/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.22.2025
Summary : Source file for the Support Skill Base.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Abilities/SupportSkills/SupportSkillBase.h"
#include "WorldSettings/IKGameState.h"

void USupportSkillBase::InitSupportSkill(const FSupportSkillData& skill_data)
{
	skill_data_ = skill_data;
}

float USupportSkillBase::GetCost() const
{
	return cost_;
}

const FSupportSkillData& USupportSkillBase::GetSupportSkillData() const
{
	return skill_data_;
}

bool USupportSkillBase::ActivateSkill(const FTargetResult& TargetResult)
{
	return Super::ActivateSkill(TargetResult);
}
