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
#include "Structs/BuffData.h"
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

float USkillBase::GetCoolTime() const
{
	return cool_time_;
}

float USkillBase::GetCastingTime() const
{
	return casting_time_;
}

void USkillBase::ApplyDamage(FDamageData DamageData)
{
	if (DamageData.attack_target_.IsValid() && DamageData.attack_target_->IsA<AUnit>())
	{
		AUnit* attack_target = Cast<AUnit>(DamageData.attack_target_);

		if (DamageData.attacker_.IsValid() && DamageData.attacker_->IsA<AUnit>())
		{
			AUnit* attacker = Cast<AUnit>(DamageData.attacker_);
			DamageData.skill_power_base_dmg_ = DamageData.skill_power_base_dmg_ + (attacker->GetCharacterStat()->GetSkillPower() * scaling_factor_);
		}

		attack_target->GetDamage(DamageData);
	}
}

bool USkillBase::ApplyBuff(FBuffData buff_data, AActor* buff_target)
{
	if (AUnit* owner_unit = Cast<AUnit>(skill_owner_))
	{
		buff_data.value_ = buff_data.value_ + (owner_unit->GetCharacterStat()->GetSkillPower() * scaling_factor_);
	}
	if (buff_target && buff_target->IsA<AUnit>())
	{
		AUnit* unit = Cast<AUnit>(buff_target);
		unit->ApplyBuff(buff_data);

		return true;
	}

	return false;
}
