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
	game_state_cache_ = Cast<AIKGameState>(UGameplayStatics::GetGameState(GetWorld()));
}

float USupportSkillBase::GetCost() const
{
	return cost_;
}

void USupportSkillBase::OnDecide()
{
	Super::OnDecide();
	UseEnergy();
}

void USupportSkillBase::UseEnergy()
{
	game_state_cache_->UseEnergy(cost_);
}