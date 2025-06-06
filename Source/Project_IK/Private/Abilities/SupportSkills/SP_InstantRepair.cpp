/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.22.2025
Summary : Source file for the Instant Repair Support SKill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/SupportSkills/SP_InstantRepair.h"

#include "Characters/Unit.h"

USP_InstantRepair::USP_InstantRepair()
{
	target_param_ = FTargetParameters(ETargetingMode::Actor, ETargetType::Allies, 1000.f);
	cool_time_ = 5.f;
	cost_ = 3.f;
}

void USP_InstantRepair::Decide(const FTargetResult& target_result)
{
	if(target_result.target_actors_[0])
	{
		AUnit* target_unit = Cast<AUnit>(target_result.target_actors_[0]);
		target_unit->AcquireShield(300.f, 3.f);
		OnDecide();
	}
}
