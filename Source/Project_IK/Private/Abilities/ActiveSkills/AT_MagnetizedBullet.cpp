/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 04.17.2025
Summary : Source file for Magnetized Bullet Active Skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Abilities/ActiveSkills/AT_MagnetizedBullet.h"
#include "Abilities/OnHitComponents/BulletMagnetizeEffectComponent.h"
#include "Characters/HeroBase.h"
#include "Components/WeaponMechanics.h"
#include "Weapons/Guns/GunBase.h"

UAT_MagnetizedBullet::UAT_MagnetizedBullet()
{
	target_param_ = FTargetParameters(ETargetingMode::Actor, ETargetType::Allies, 0.f, 0.f, true);
	cool_time_ = 5.f;
	duration_ = 3.f;
}

bool UAT_MagnetizedBullet::ActivateSkill(const FTargetResult& TargetResult)
{
	if (AHeroBase* hero = Cast<AHeroBase>(skill_owner_))
	{
		if (auto weapon_actor = hero->GetWeaponMechanics()->GetWeaponActor())
		{
			weapon_actor->AddOnHitComponent(magnetized_on_hit_class_);
		}
		//만약 A급일 시, 지속시간 동안 공격속도 15% 증가.
		if (IsUpgradedActiveSkill(skill_data_.type_))
		{
			// FBuffStatusData status_data = {ECharacterStatType::AttackSpeed, 1.15, true, false, duration_};
			// hero->ApplyStatusBuff(EBuffType::MagnetizedBullet_A, status_data);
			// hero->AddBuffUI({skill_data_.item_data_, EBuffType::MagnetizedBullet_A, duration_});
		}
		//hero->AddBuffUI({skill_data_.item_data_, EBuffType::MagnetizedBullet_A, duration_, false});
		FTimerDelegate timer_delegate = FTimerDelegate::CreateUObject(this, &UAT_MagnetizedBullet::OnFinishSkill);
		GetWorld()->GetTimerManager().SetTimer(duration_timer_handle_, timer_delegate, duration_, false);
	}
	return 	Super::ActivateSkill(TargetResult);
}

void UAT_MagnetizedBullet::OnFinishSkill()
{
	if (AHeroBase* owner_hero_ptr = Cast<AHeroBase>(skill_owner_))
	{
		if (auto weapon_actor = owner_hero_ptr->GetWeaponMechanics()->GetWeaponActor())
		{
			weapon_actor->RemoveOnHitComponent(magnetized_on_hit_class_);
		}
		GetWorld()->GetTimerManager().ClearTimer(duration_timer_handle_);
	}
}