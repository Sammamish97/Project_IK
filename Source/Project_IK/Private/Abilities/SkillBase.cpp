/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 06/14/2025
Summary : Source file for skill base.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Abilities/SkillBase.h"

FTargetParameters USkillBase::GetTargetParameters() const
{
	return target_param_;
}

float USkillBase::GetCoolTime() const
{
	return cool_time_;
}

void USkillBase::UpdateCoolDown(float cool_down)
{
	on_activate_skill_.Broadcast(cool_down);
}

bool USkillBase::ActivateSkill(const FTargetResult& TargetResult)
{
	UpdateCoolDown(cool_time_);
	return true;
}

void USkillBase::ResetSkill()
{
}
