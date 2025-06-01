/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.22.2025
Summary : Source file for the Support Skill Base.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Abilities/SupportSkills/SupportSkillBase.h"

#include "Kismet/GameplayStatics.h"
#include "WorldSettings/IKPlayerController.h"

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

bool USupportSkillBase::ActivateSkill()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(cool_down_handle_) == false)
	{
		auto controller = Cast<AIKPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
		controller->StartTargeting(target_param_, ETargetingState::SupportSkill);
		return true;
	}
	return false;
}

void USupportSkillBase::Reset()
{
}

void USupportSkillBase::Decide(const FTargetResult& TargetResult)
{
	
}

void USupportSkillBase::BeginCoolDown()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(cool_down_handle_) == false)
	{
		GetWorld()->GetTimerManager().SetTimer(cool_down_handle_, cool_time_, false);
	}
}
