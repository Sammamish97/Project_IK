/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.1.2025
Summary : Header file for the Instant Repair Support SKill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Abilities/SupportSkills/SP_Reposition.h"
#include "Characters/HeroBase.h"
#include "Kismet/GameplayStatics.h"
#include "WorldSettings/IKPlayerController.h"

USP_Reposition::USP_Reposition()
{
	target_param_ = FTargetParameters(ETargetingMode::Actor, ETargetType::Allies, 10000.f);
	reposition_location_params_ = FTargetParameters(ETargetingMode::Location, ETargetType::None, 1000.f, 1000.f);
	cool_time_ = 1.f;
	cost_ = 3.f;
}

void USP_Reposition::Reset()
{
	Super::Reset();
	selected_hero_ = nullptr;
}

void USP_Reposition::Decide(const FTargetResult& target_result)
{
	if (selected_hero_)
	{
		selected_hero_->Reposition(target_result.target_location_);
		OnDecide();
	}
	else
	{
		if (target_result.target_actors_.Num() > 0 && target_result.target_actors_[0]->IsA(AHeroBase::StaticClass()))
		{
			player_controller_cache_->ClearTargetingState();
			selected_hero_ = Cast<AHeroBase>(target_result.target_actors_[0]);
			player_controller_cache_->StartTargeting(reposition_location_params_, ETargetingState::SupportSkill);
		}
	}
}