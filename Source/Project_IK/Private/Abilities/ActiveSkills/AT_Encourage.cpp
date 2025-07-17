/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 04.19.2025
Summary : Source file for an active skill named Encourage.
					Buffs of attack speed & skill cool-time in a range of allies.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/ActiveSkills/AT_Encourage.h"

#include "Structs/TargetResult.h"
#include "Structs/BuffStatusData.h"

#include "Characters/HeroBase.h"

UAT_Encourage::UAT_Encourage()
{
	target_param_ = FTargetParameters(ETargetingMode::Location, ETargetType::Allies, 0.f, 1000.f, true);

	cool_time_ = 10.f;
	scaling_factor_ = 0.02f;

	buff_duration_ = 4.f;
	attack_power_buff_amount_ = 2.f;
	skill_power_buff_amount_ = 2.f;
	shield_amount_ = 500.f;
}

bool UAT_Encourage::ActivateSkill(const FTargetResult& TargetResult)
{
	//실드 + 공격력 + 스킬 위력
	FBuffStatusData attack_power_buff_data = {ECharacterStatType::AttackPower, attack_power_buff_amount_, true, false ,buff_duration_};
	FBuffStatusData skill_power_buff_data = {ECharacterStatType::SkillPower, skill_power_buff_amount_, true, false ,buff_duration_};
	
	for (AActor* ally : TargetResult.target_actors_)
	{
		if (AHeroBase* casted_hero = Cast<AHeroBase>(ally))
		{
			casted_hero->ApplyBuff(EBuffType::Encourage, attack_power_buff_data);
			casted_hero->ApplyBuff(EBuffType::Encourage, skill_power_buff_data);
			casted_hero->AcquireShield(shield_amount_, buff_duration_);
			casted_hero->AddBuffUI({skill_data_.item_data_, EBuffType::Encourage, buff_duration_});
			if (IsUpgradedActiveSkill(skill_data_.type_))
			{
				casted_hero->ReduceActiveSkillCoolDown(1.f);
			}
		}
	}

	return Super::ActivateSkill(TargetResult);
}
