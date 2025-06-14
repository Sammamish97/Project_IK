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
#include "WorldSettings/IKGameState.h"
#include "WorldSettings/IKPlayerController.h"

void USupportSkillBase::InitSupportSkill()
{
	player_controller_cache_ = Cast<AIKPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	game_state_cache_ = Cast<AIKGameState>(UGameplayStatics::GetGameState(GetWorld()));
}

float USupportSkillBase::GetCost() const
{
	return cost_;
}

bool USupportSkillBase::ActivateSkill()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(cool_down_handle_) == false)
	{
		
		player_controller_cache_->StartTargeting(target_param_, ETargetingState::SupportSkill);
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

void USupportSkillBase::OnDecide()
{
	player_controller_cache_->FinishTargeting();
	Reset();
	UseEnergy();
	BeginCoolDown();
	on_decide_.Broadcast(cool_time_);
}

void USupportSkillBase::BeginCoolDown()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(cool_down_handle_) == false)
	{
		GetWorld()->GetTimerManager().SetTimer(cool_down_handle_, cool_time_, false);
	}
}

void USupportSkillBase::UseEnergy()
{
	game_state_cache_->UseEnergy(cost_);
}