/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.21.2024
Summary : Source file for Skill base class.
					It will be used like a pure virtual class. A skill class will derived it.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/SkillBase.h"

#include "Structs/DamageData.h"
#include "Characters/Unit.h"
#include "Components/CharacterStatComponent.h"

void USkillBase::InitActiveSkill(AActor* skill_owner)
{
	skill_owner_ = skill_owner;
}

FTargetParameters USkillBase::GetTargetParameters() const
{
	return target_param_;
}

float USkillBase::GetCooltime() const
{
	return cool_time_;
}

void USkillBase::ApplyDamage(FDamageData DamageData)
{
	if (DamageData.attack_target.IsValid() && DamageData.attack_target->IsA<AUnit>())
	{
		AUnit* attack_target = Cast<AUnit>(DamageData.attack_target);

		if (DamageData.attacker.IsValid() && DamageData.attacker->IsA<AUnit>())
		{
			AUnit* attacker = Cast<AUnit>(DamageData.attacker);
			DamageData.damage = DamageData.damage + (attacker->GetCharacterStat()->GetActiveSkillPower() * scaling_factor_);
		}

		attack_target->GetDamage(DamageData);
	}
}