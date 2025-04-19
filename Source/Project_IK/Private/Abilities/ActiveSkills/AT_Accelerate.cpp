/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.15.2025
Summary : Source file for Accelerate Active Skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/ActiveSkills/AT_Accelerate.h"
#include "Characters/HeroBase.h"
#include "Components/WeaponMechanics.h"
#include "Structs/BuffData.h"

UAT_Accelerate::UAT_Accelerate()
{
	target_param_ = FTargetParameters(ETargetingMode::Actor, ETargetType::Allies, 1000.f);

	cool_time_ = 5.f;
}

bool UAT_Accelerate::ActivateSkill_Implementation(const FTargetResult& TargetResult)
{
	TWeakObjectPtr<AHeroBase> owner_hero_ptr = Cast<AHeroBase>(skill_owner_);
	if (auto hero = owner_hero_ptr.Get())
	{
		auto weapon_mechanics_cache = hero->GetWeaponMechanics();
		weapon_mechanics_cache->Reload(0.5);
		owner_hero_ptr->ApplyBuff(FBuffData("Accelerate Buff", ECharacterStatType::AttackSpeed, attack_speed_increase_amount_, true, buff_duration_));
		hero->AcquireShield(shield_amount_, buff_duration_);
		return true;
	}
	return false;
}
