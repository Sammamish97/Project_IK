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

#include "Structs/DamageData.h"
#include "Structs/TargetResult.h"

#include "Kismet/GameplayStatics.h"
#include "WorldSettings/IKGameModeBase.h"

#include "Abilities/ActiveSkills/ThunderStorm.h"

UAT_ThunderStorm::UAT_ThunderStorm()
{
	target_param_ = FTargetParameters(ETargetingMode::Location, ETargetType::Opponents, 1000.f, 2000.f);

	cool_time_ = 12.f;
	scaling_factor_ = 0.8f;
	damage_ = 120.f;
}

bool UAT_ThunderStorm::ActivateSkill_Implementation(const FTargetResult& TargetResult)
{
	world_cache_ = skill_owner_->GetWorld();

	if (!world_cache_)
	{
		return false;
	}

	world_cache_->GetTimerManager().SetTimer(
		damage_handler_,
		this,
		&UAT_ThunderStorm::DamageEnemies,
		0.5f,
		true,
		0.5f
	);

	storm_location = TargetResult.target_location_;

	FActorSpawnParameters spawn_params;
	spawn_params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	visual_actor_ = world_cache_->SpawnActor<AThunderStorm>(visual_actor_class_, storm_location, FRotator::ZeroRotator, spawn_params);
	if (visual_actor_)
	{
		visual_actor_->SetSphereRadius(target_param_.radius_);
	}

	return true;
}

void UAT_ThunderStorm::DamageEnemies()
{
	// @@ It damages enemies in this instead of an actor named ThunderStorm.

	storm_damage_count_ += 1;

	float squared_radius = target_param_.radius_ * target_param_.radius_;

	AIKGameModeBase* game_mode = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(world_cache_));
	if (game_mode)
	{
		const TArray<AActor*> enemies = game_mode->GetEnemyContainers();
		for (AActor* enemy : enemies)
		{
			FVector to_actor = enemy->GetActorLocation() - storm_location;

			float squared_distance_to_actor = to_actor.SizeSquared();
			if (squared_distance_to_actor <= squared_radius)
			{
				ApplyDamage({ 0.f, damage_, EDamageType::Magic, skill_owner_, enemy });
			}
		}
	}

	if (storm_damage_count_ >= 4)
	{
		world_cache_->GetWorld()->GetTimerManager().ClearTimer(damage_handler_);
		visual_actor_->Destroy();
	}
}
