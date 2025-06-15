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

float USupportSkillBase::GetCost() const
{
	return cost_;
}

bool USupportSkillBase::ActivateSkill(const FTargetResult& TargetResult)
{
	Super::ActivateSkill(TargetResult);
	return true;
}