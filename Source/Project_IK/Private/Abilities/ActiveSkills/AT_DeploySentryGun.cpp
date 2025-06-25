/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 04.22.2025
Summary : Source file for an active skill named DeployCover.
					It deploys a sentry gun on the battlefield.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/ActiveSkills/AT_DeploySentryGun.h"

#include "Environments/Cover.h"
#include "Characters/Unit.h"
#include "Components/CharacterStatComponent.h"

#include "Structs/TargetParameters.h"
#include "Structs/TargetResult.h"

UAT_DeploySentryGun::UAT_DeploySentryGun()
{
	target_param_ = FTargetParameters(ETargetingMode::Location, ETargetType::None, 1000.f, 100.f);

	cool_time_ = 15.f;
}

bool UAT_DeploySentryGun::ActivateSkill(const FTargetResult& TargetResult)
{
	if (actor_class_)
	{
		actor_ = skill_owner_->GetWorld()->SpawnActor<ACover>(actor_class_, TargetResult.target_location_, FRotator::ZeroRotator);
		AUnit* owner_unit = Cast<AUnit>(skill_owner_);
		actor_->SetHitPoints(deployed_sentry_hit_points_ + owner_unit->GetCharacterStat()->GetSkillPower() * hit_points_scaling_factor_);
	}
	return Super::ActivateSkill(TargetResult);
}
