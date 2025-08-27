/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.26.2024
Summary : Source file for skill containers.
					An actor component class to contain skills.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Components/ActiveSkillMechanics.h"

#include "AIController.h"
#include "Abilities/ActiveSkills/ActiveSkillBase.h"
#include "Characters/HeroBase.h"
#include "BrainComponent.h"

#include "Components/CharacterStatComponent.h"
#include "Components/WeaponMechanics.h"

// Sets default values for this component's properties
UActiveSkillMechanics::UActiveSkillMechanics()
	: Super::UActorComponent(), equipped_active_skill_data_(), active_skill_(nullptr), hero_cache_(nullptr)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	bWantsInitializeComponent = true;
}

void UActiveSkillMechanics::BeginPlay()
{
	Super::BeginPlay();
	hero_cache_ = Cast<AHeroBase>(GetOwner());
}

void UActiveSkillMechanics::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearTimer(casting_time_handle_);
	Super::EndPlay(EndPlayReason);
}

void UActiveSkillMechanics::InitializeComponent()
{
	Super::InitializeComponent();
}

void UActiveSkillMechanics::ActivateSkill(const FTargetResult& target_result)
{
	if (HasActiveSkill())
	{
		if (active_skill_->HasMotion())
		{
			if (auto casted_hero = Cast<AHeroBase>(hero_cache_))
			{
				casted_hero->SetUnitStateWithInterrupt(EUnitState::OnActiveSkill);
				casted_hero->GetWeaponMechanics()->FinishFire();
				if (target_result.target_actors_.Num() > 0)
				{
					Cast<AAIController>(casted_hero->GetController())->SetFocus(target_result.target_actors_[0]);
				}
				else
				{
					Cast<AAIController>(casted_hero->GetController())->SetFocalPoint(target_result.target_location_);
				}
				active_skill_->OnEnterCasting();

				auto& timer_manager = GetWorld()->GetTimerManager();
				
				FTimerDelegate casting_delegate = FTimerDelegate::CreateUObject(this, &UActiveSkillMechanics::OnFinishCasting, target_result);
				FTimerDelegate ai_holding_delegate = FTimerDelegate::CreateUObject(this, &UActiveSkillMechanics::OnFinishAIHolding);

				timer_manager.SetTimer(casting_time_handle_, casting_delegate, active_skill_->GetCastingTime(), false);
				timer_manager.SetTimer(ai_hold_time_handle_, ai_holding_delegate, active_skill_->GetAIHoldTime(), false);
			}
		}
		else
		{
			active_skill_->ActivateSkill(target_result);
		}
	}
}

void UActiveSkillMechanics::StopActiveSkill()
{
	GetWorld()->GetTimerManager().ClearTimer(casting_time_handle_);
	GetWorld()->GetTimerManager().ClearTimer(ai_hold_time_handle_);
}

FTargetParameters UActiveSkillMechanics::GetTargetParameters() const
{
	return active_skill_->GetTargetParameters();
}

bool UActiveSkillMechanics::HasActiveSkill() const
{
	return active_skill_ != nullptr;
}

float UActiveSkillMechanics::GetCooltime() const
{
	if (active_skill_)
	{
		return active_skill_->GetCoolTime() * (100 / (100 + hero_cache_->GetCharacterStat()->GetSkillCooldown()));
	}
	return 0.f;
}

float UActiveSkillMechanics::GetCastingTime() const
{
	if (active_skill_)
	{
		return active_skill_->GetCastingTime();
	}
	return 0.f;
}

void UActiveSkillMechanics::OnFinishCasting(FTargetResult target_result)
{
	if (active_skill_)
	{
		active_skill_->ActivateSkill(target_result);
	}
}

void UActiveSkillMechanics::OnFinishAIHolding()
{
	if (auto casted_hero = Cast<AHeroBase>(hero_cache_))
	{
		casted_hero->ResetUnitState();
		casted_hero->FinishAction();
	}
}

const FActiveSkillData& UActiveSkillMechanics::GetEquippedActiveSkillData()
{
	return equipped_active_skill_data_;
}

USkillBase* UActiveSkillMechanics::GetActiveSkill() const
{
	return active_skill_;
}

void UActiveSkillMechanics::EquipActiveSkill(const FActiveSkillData& data)
{
	if (data.type_ != EActiveSkillType::INVALID)
	{
		if (active_skill_)
		{
			UnEquipActiveSkill();
		}
		equipped_active_skill_data_ = data;
		active_skill_ = NewObject<UActiveSkillBase>(this, equipped_active_skill_data_.active_skill_class);
		active_skill_->InitActiveSkill(hero_cache_.Get(), equipped_active_skill_data_);
	}
}

void UActiveSkillMechanics::UnEquipActiveSkill()
{
	equipped_active_skill_data_ = FActiveSkillData();
	active_skill_ = nullptr;
}