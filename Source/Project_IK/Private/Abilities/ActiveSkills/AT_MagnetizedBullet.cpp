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
		if (skill_data_.IsUpgraded())
		{
			FBuffStatusData status_data = {ECharacterStatType::AttackSpeed, 2.0, true, false, duration_};
			hero->ApplyBuff(EBuffType::MagnetizedBullet_A, status_data);
			//IKTODO: 버프 Data 추가하기. 추가하기 전, Buff에 의해 Text가 3개가 되어 로컬라이징에서 일어나는 문제를 해결해야 함.
			//hero->AddBuffUI()
		}
		hero->AddBuffUI({skill_data_.item_data_, EBuffType::MagnetizedBullet_A, duration_, false});
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