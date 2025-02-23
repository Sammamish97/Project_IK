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
	cool_time_ = 5.f;
	target_param_.radius_ = 50;
	target_param_.range_ = 50;
	target_param_.current_mode_ = ETargetingMode::Actor;
	target_param_.target_type_ = ETargetType::Opponents;
}

bool UAT_Thunder::ActivateSkill_Implementation(const FTargetResult& target_result)
{
	if(target_result.target_actors_[0])
	{
		FDamageData thunder_damage_data = {damage_, EDamageType::Magic, skill_owner_, target_result.target_actors_[0] };
		Cast<AUnit>(target_result.target_actors_[0])->GetDamage(thunder_damage_data);
		return true;
	}
	return false;
}
