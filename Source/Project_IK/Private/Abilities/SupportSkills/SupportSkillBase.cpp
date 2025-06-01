/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.22.2025
Summary : Source file for the Support Skill Base.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Abilities/SupportSkills/SupportSkillBase.h"

FTargetParameters USupportSkillBase::GetTargetParameters() const
{
	return target_param_;
}

float USupportSkillBase::GetCoolTime() const
{
	return cool_time_;
}

float USupportSkillBase::GetCost() const
{
	return cost_;
}

bool USupportSkillBase::ActivateSkill(const FTargetResult& TargetResult)
{
	if (GetWorld()->GetTimerManager().IsTimerActive(cool_down_handle_) == false)
	{
		GetWorld()->GetTimerManager().SetTimer(cool_down_handle_, cool_time_, false, -1);
		return true;
	}
	return false;
}
