/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.12.2025
Summary : Source file for Ricochet active skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/ActiveSkills/AT_Ricochet.h"

#include "Characters/HeroBase.h"
#include "Abilities/OnHitComponents/BulletChainEffectComponent.h"
#include "Components/WeaponMechanics.h"
#include "Weapons/Guns/GunBase.h"

class AHeroBase;

UAT_Ricochet::UAT_Ricochet()
{
	target_param_ = FTargetParameters(ETargetingMode::Actor, ETargetType::Allies, 0.f, 0.f, true);
	cool_time_ = 5.f;
	duration_ = 3.f;
}

bool UAT_Ricochet::ActivateSkill(const FTargetResult& TargetResult)
{
	if (AHeroBase* hero = Cast<AHeroBase>(skill_owner_))
	{
		if (auto weapon_actor = hero->GetWeaponMechanics()->GetWeaponActor())
		{
			weapon_actor->AddOnHitComponent(chain_on_hit_class_);
		}
		hero->AddBuffUI({skill_data_.item_data_, EBuffType::Ricochet, duration_, false});

		FTimerDelegate timer_delegate = FTimerDelegate::CreateUObject(this, &UAT_Ricochet::OnFinishSkill);
		GetWorld()->GetTimerManager().SetTimer(duration_timer_handle_, timer_delegate, duration_, false);
	}
	return Super::ActivateSkill(TargetResult);
}

void UAT_Ricochet::OnFinishSkill()
{
	if (AHeroBase* owner_hero_ptr = Cast<AHeroBase>(skill_owner_))
	{
		if (auto weapon_actor = owner_hero_ptr->GetWeaponMechanics()->GetWeaponActor())
		{
			weapon_actor->RemoveOnHitComponent(chain_on_hit_class_);
		}
		GetWorld()->GetTimerManager().ClearTimer(duration_timer_handle_);
	}
}
