/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.12.2025
Summary : Source file for TripleFire Active Skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Abilities/ActiveSkills/AT_TripleFire.h"

#include "Characters/HeroBase.h"
#include "Components/CharacterStatComponent.h"
#include "Subsystems/DelegateBridgeSubsystem.h"

UAT_TripleFire::UAT_TripleFire()
{
	target_param_ = FTargetParameters(ETargetingMode::Actor, ETargetType::Opponents, 1000.f);

	cool_time_ = 5.f;
}

void UAT_TripleFire::InitActiveSkill(AActor* skill_owner, const FActiveSkillData& skill_data)
{
	Super::InitActiveSkill(skill_owner, skill_data);
	bool bind_result = GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnFireWeapon(skill_owner, this, &UAT_TripleFire::OnTripleFire);
	if (bind_result == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("BindOnFireWeapon has failed in UAT_TripleFire::OnTripleFire."));
		check(TEXT("BindOnFireWeapon has failed in UAT_TripleFire::OnTripleFire."));
	}
	buff_status_data_.stat_type_ = ECharacterStatType::AttackSpeed;
	buff_status_data_.value_ = attack_speed_buff_amount_;
	buff_status_data_.is_percentage_ = false;
	buff_status_data_.is_permanent_ = true;
	if (IsUpgradedActiveSkill(skill_data_.type_))
	{
		buff_status_data_.value_ = upgraded_buff_amount_;
	}
}

bool UAT_TripleFire::ActivateSkill(const FTargetResult& TargetResult)
{
	TWeakObjectPtr<AHeroBase> owner_hero_ptr = Cast<AHeroBase>(skill_owner_);
	if (auto hero = owner_hero_ptr.Get())
	{
		TWeakObjectPtr<AActor> target_ptr = TargetResult.target_actors_[0];
		if (auto target = target_ptr.Get())
		{
			on_triple_fire_ = true;
			hero->SetAttackTarget(target);
			hero->ApplyStatusBuff(EBuffType::TripleFire, buff_status_data_);
			//hero->AddBuffUI({skill_data_.item_data_, EBuffType::TripleFire, 0.f, true  });
		}
	}
	return Super::ActivateSkill(TargetResult);
}

void UAT_TripleFire::OnTripleFire()
{
	if (on_triple_fire_)
	{
		fire_counter_ += 1;
		if (fire_counter_  >= 3)
		{
			fire_counter_ = 0;
			on_triple_fire_ = false;
			TWeakObjectPtr<AHeroBase> owner_hero_ptr = Cast<AHeroBase>(skill_owner_);
			if (auto hero = owner_hero_ptr.Get())
			{
				hero->RemoveBuffUI(EBuffType::TripleFire);
				hero->RemoveBuff(EBuffType::TripleFire);
			}
		}
	}
}