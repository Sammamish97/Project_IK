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

#include "Abilities/Buffs/BuffBase.h"
#include "Structs/TargetResult.h"
#include "Structs/BuffStatusData.h"
#include "Characters/HeroBase.h"

//IKTODO: 실드에 계수를 추가하는것도 좋을듯 하다.
UAT_Encourage::UAT_Encourage()
{
	target_param_ = FTargetParameters(ETargetingMode::Location, ETargetType::Allies, 0.f, 1000.f, true);

	cool_time_ = 10.f;
	scaling_factor_ = 0.02f;
}

void UAT_Encourage::InitActiveSkill(AActor* skill_owner, const FActiveSkillData& skill_data)
{
	Super::InitActiveSkill(skill_owner, skill_data);
	buff_ = NewObject<UBuffBase>(this, buff_class_);
}

void UAT_Encourage::OnEnterCasting()
{
	Super::OnEnterCasting();
	Cast<AUnit>(skill_owner_)->PlayAnimMontage(casting_anim_montage_);
}

bool UAT_Encourage::ActivateSkill(const FTargetResult& TargetResult)
{
	for (AActor* ally : TargetResult.target_actors_)
	{
		if (AHeroBase* casted_hero = Cast<AHeroBase>(ally))
		{
			buff_->ApplyBuff(casted_hero);
			if (IsUpgradedActiveSkill(skill_data_.type_))
			{
				casted_hero->ReduceActiveSkillCoolDown(1.f);
			}
		}
	}

	return Super::ActivateSkill(TargetResult);
}
