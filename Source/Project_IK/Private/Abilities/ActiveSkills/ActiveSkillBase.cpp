/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.21.2024
Summary : Source file for Skill base class.
					It will be used like a pure virtual class. A skill class will derived it.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/ActiveSkills/ActiveSkillBase.h"

#include "Structs/DamageData.h"
#include "Structs/BuffStatusData.h"
#include "Characters/Unit.h"
#include "Components/CharacterStatComponent.h"

TOptional<FTargetParameters> UActiveSkillBase::ActivateSkill(const FTargetResult& TargetResult)
{
	return Super::ActivateSkill(TargetResult);
}

void UActiveSkillBase::InitActiveSkill(AActor* skill_owner)
{
	skill_owner_ = skill_owner;
}

float UActiveSkillBase::GetCastingTime() const
{
	return casting_time_;
}

void UActiveSkillBase::ApplyDamage(FDamageData DamageData)
{
	if (DamageData.attack_target.IsValid() && DamageData.attack_target->IsA<AUnit>())
	{
		AUnit* attack_target = Cast<AUnit>(DamageData.attack_target);

		if (DamageData.attacker.IsValid() && DamageData.attacker->IsA<AUnit>())
		{
			AUnit* attacker = Cast<AUnit>(DamageData.attacker);
			DamageData.skill_power_base_dmg = DamageData.skill_power_base_dmg + (attacker->GetCharacterStat()->GetSkillPower() * scaling_factor_);
		}

		attack_target->GetDamage(DamageData);
	}
}

bool UActiveSkillBase::ApplyBuff(FBuffStatusData buff_data, AActor* buff_target)
{
	if (AUnit* owner_unit = Cast<AUnit>(skill_owner_))
	{
		buff_data.value_ = buff_data.value_ + (owner_unit->GetCharacterStat()->GetSkillPower() * scaling_factor_);
	}
	if (buff_target && buff_target->IsA<AUnit>())
	{
		AUnit* unit = Cast<AUnit>(buff_target);
		//IKTODO: 테스트 후 버프 적용
		//unit->ApplyBuff(buff_data);

		return true;
	}

	return false;
}
