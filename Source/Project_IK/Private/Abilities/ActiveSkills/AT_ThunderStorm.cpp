/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 04.18.2025
Summary : Source file for an active skill named ThunderStorm.
					It periodically summons thunders that damages in an area.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/ActiveSkills/AT_ThunderStorm.h"

#include "Structs/TargetResult.h"

#include "Abilities/ActiveSkills/ThunderStorm.h"

UAT_ThunderStorm::UAT_ThunderStorm()
{
	target_param_ = FTargetParameters(ETargetingMode::Location, ETargetType::Opponents, 1000.f, 2000.f);

	cool_time_ = 12.f;
	scaling_factor_ = 0.8f;
	damage_ = 120.f;
}

bool UAT_ThunderStorm::ActivateSkill(const FTargetResult& TargetResult)
{
	Super::ActivateSkill(TargetResult);
	
	world_cache_ = skill_owner_->GetWorld();
	FActorSpawnParameters spawn_params;
	spawn_params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	visual_actor_ = world_cache_->SpawnActor<AThunderStorm>(visual_actor_class_, TargetResult.target_location_, FRotator::ZeroRotator, spawn_params);
	if (visual_actor_)
	{
		visual_actor_->SetNecessaryData(target_param_.radius_, scaling_factor_, damage_, skill_owner_);
	}

	return Super::ActivateSkill(TargetResult);
}

void UAT_ThunderStorm::DamageEnemies()
{
}
