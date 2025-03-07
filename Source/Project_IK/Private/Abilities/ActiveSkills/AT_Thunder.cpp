/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.22.2025
Summary : Header file for Thunder Active Skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/ActiveSkills/AT_Thunder.h"

#include "Characters/Unit.h"

UAT_Thunder::UAT_Thunder()
{
	target_param_ = FTargetParameters(ETargetingMode::Actor, ETargetType::Opponents, 1000.f);

	cool_time_ = 5.f;

	damage_ = 50.f;
}

bool UAT_Thunder::ActivateSkill_Implementation(const FTargetResult& target_result)
{
	if(target_result.target_actors_[0])
	{
		ApplyDamage({ damage_, EDamageType::Magic, skill_owner_, target_result.target_actors_[0] });
		return true;
	}
	return false;
}
