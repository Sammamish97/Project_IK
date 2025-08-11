/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.24.2025
Summary : Source file for one Maintain support skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/SupportSkills/SP_Maintain.h"
#include "Characters/HeroBase.h"

USP_Maintain::USP_Maintain()
{
	target_param_ = FTargetParameters(ETargetingMode::Actor, ETargetType::Allies, 10000.f);
}

bool USP_Maintain::ActivateSkill(const FTargetResult& target_result)
{
	if (target_result.target_actors_.Num() > 0 && target_result.target_actors_[0]->IsA(AHeroBase::StaticClass()))
	{
		if (auto casted_hero = Cast<AHeroBase>(target_result.target_actors_[0]))
		{
			casted_hero->BeginMaintaining();
		}
	}
	return true;
}