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
#include "Structs/BuffStatusData.h"

UAT_Accelerate::UAT_Accelerate()
{
	target_param_ = FTargetParameters(ETargetingMode::Actor, ETargetType::Allies, 1000.f);

	cool_time_ = 5.f;

	buff_data_.buff_type_ = EBuffType::Accelerate;
	buff_data_.duration_ = buff_duration_;
	buff_data_.thumbnail = nullptr;
	//buff_data_.buff_status_.Push(FBuffStatusData(ECharacterStatType::AttackSpeed, 1.5f, true));
}

bool UAT_Accelerate::ActivateSkill(const FTargetResult& TargetResult)
{
	TWeakObjectPtr<AHeroBase> owner_hero_ptr = Cast<AHeroBase>(skill_owner_);
	if (auto hero = owner_hero_ptr.Get())
	{
		auto weapon_mechanics_cache = hero->GetWeaponMechanics();
		weapon_mechanics_cache->Reload(0.5);
		//owner_hero_ptr->ApplyBuff(buff_data_);
		hero->AcquireShield(shield_amount_, buff_duration_);
	}
	return Super::ActivateSkill(TargetResult);
}
