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
#include "Characters/HeroBase.h"
#include "Components/CharacterStatComponent.h"

bool UActiveSkillBase::ActivateSkill(const FTargetResult& TargetResult)
{
	bool result = Super::ActivateSkill(TargetResult);
	UpdateCoolDown(cool_time_);
	Cast<AHeroBase>(skill_owner_)->DispatchUnitEvent(EUnitEvent::OnActiveSkill);
	return result;
}

void UActiveSkillBase::InitActiveSkill(AActor* skill_owner, const FActiveSkillData& skill_data)
{
	skill_owner_ = skill_owner;
	skill_data_ = skill_data;
	cool_time_ = skill_data.cool_time_;
}

bool UActiveSkillBase::CanActivateSkill(const FTargetResult& TargetResult)
{
	return Super::CanActivateSkill(TargetResult);
}

float UActiveSkillBase::GetCastingTime() const
{
	return casting_time_;
}

float UActiveSkillBase::GetAIHoldTime() const
{
	return ai_holding_time_;
}

float UActiveSkillBase::GetCoolTime() const
{
	return skill_data_.cool_time_;
}

float UActiveSkillBase::GetCoolDown() const
{
	return cool_time_;
}

bool UActiveSkillBase::HasMotion() const
{
	return has_casting_motion_;
}

void UActiveSkillBase::OnEnterCasting()
{
	//이 함수를 상속하여 애니메이션 재생을 행해야 한다.
}

void UActiveSkillBase::ApplyDamage(FDamageData DamageData)
{
	if (DamageData.attack_target_.IsValid() && DamageData.attack_target_->IsA<AUnit>())
	{
		AUnit* attack_target = Cast<AUnit>(DamageData.attack_target_);

		if (DamageData.attacker_.IsValid() && DamageData.attacker_->IsA<AUnit>())
		{
			AUnit* attacker = Cast<AUnit>(DamageData.attacker_);
			DamageData.skill_power_base_dmg_ = DamageData.skill_power_base_dmg_ + (attacker->GetCharacterStat()->GetSkillPower() * skill_data_.skill_power_scales_[0]);
		}
		attack_target->GetDamage(DamageData);
	}
}
