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
#include "Structs/BuffData.h"

#include "Characters/Unit.h"

UAT_Encourage::UAT_Encourage()
{
	target_param_ = FTargetParameters(ETargetingMode::Location, ETargetType::Allies, 0.f, 1000.f, true);

	cool_time_ = 10.f;
	scaling_factor_ = 0.02f;
}

bool UAT_Encourage::ActivateSkill_Implementation(const FTargetResult& TargetResult)
{
	FBuffData attack_speed("Encourage_AttackSpeed", ECharacterStatType::AttackSpeed, 1.15f, true, 8.f);
	FBuffData cooldown("Encourage_Cooldown", ECharacterStatType::SkillCoolDown, 10.f, false, 8.f);

	for (AActor* ally : TargetResult.target_actors_)
	{
		ApplyBuff(attack_speed, ally);
		ApplyBuff(cooldown, ally);
	}

	return true;
}
