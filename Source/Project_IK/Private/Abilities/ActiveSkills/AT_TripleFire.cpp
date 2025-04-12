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
#include "Components/WeaponMechanics.h"

UAT_TripleFire::UAT_TripleFire()
{
	target_param_ = FTargetParameters(ETargetingMode::Actor, ETargetType::Opponents, 1000.f);

	cool_time_ = 5.f;
}

bool UAT_TripleFire::ActivateSkill_Implementation(const FTargetResult& TargetResult)
{
	TWeakObjectPtr<AHeroBase> owner_hero_ptr = Cast<AHeroBase>(skill_owner_);
	if (owner_hero_ptr.IsValid())
	{
		AHeroBase* hero = owner_hero_ptr.Get();
		TWeakObjectPtr<AActor> target_ptr = TargetResult.target_actors_[0];
		if (target_ptr.IsValid())
		{
			AActor* target = target_ptr.Get();
			hero->SetAttackTarget(target);
			auto weapon_mechanics_cache = hero->GetWeaponMechanics();
			weapon_mechanics_cache->BeginTripleFire(target);
			return true;
		}
	}
	return false;
}
