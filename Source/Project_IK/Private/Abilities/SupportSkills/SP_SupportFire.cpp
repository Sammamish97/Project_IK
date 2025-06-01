/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.22.2025
Summary : Source file for the support fire Support Skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/SupportSkills/SP_SupportFire.h"

#include "Characters/Unit.h"

USP_SupportFire::USP_SupportFire()
{
	target_param_ = FTargetParameters(ETargetingMode::Actor, ETargetType::Opponents, 1000.f);
	cool_time_ = 5.f;
	cost_ = 3.f;
	dmg_data_ = FDamageData(100, 0, EDamageType::Projectile);
}

bool USP_SupportFire::ActivateSkill(const FTargetResult& target_result)
{
	if (Super::ActivateSkill(target_result))
	{
		if(target_result.target_actors_[0])
		{
			dmg_data_.attack_target = target_result.target_actors_[0];
			if (dmg_data_.attack_target.IsValid() && dmg_data_.attack_target->IsA<AUnit>())
			{
				AUnit* attack_target = Cast<AUnit>(dmg_data_.attack_target);
				attack_target->GetDamage(dmg_data_);
				return true;
			}
		}
	}
	return false;
}
