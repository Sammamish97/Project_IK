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
#include "Characters/HeroBase.h"
#include "Components/CharacterStatComponent.h"

bool UActiveSkillBase::ActivateSkill(const FTargetResult& TargetResult)
{
	bool result = Super::ActivateSkill(TargetResult);
	Cast<AHeroBase>(skill_owner_)->DispatchUnitEvent(EUnitEvent::OnActiveSkill);
	return result;
}

void UActiveSkillBase::InitActiveSkill(AActor* skill_owner, const FActiveSkillData& skill_data)
{
	skill_owner_ = skill_owner;
	skill_data_ = skill_data;
}

float UActiveSkillBase::GetCastingTime() const
{
	return casting_time_;
}

void UActiveSkillBase::ApplyDamage(FDamageData DamageData)
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