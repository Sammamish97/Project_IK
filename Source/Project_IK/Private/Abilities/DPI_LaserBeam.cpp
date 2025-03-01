/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 12.21.2024
Summary : Source file for the DPI that fire laser beams.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/DPI_LaserBeam.h"

#include "Kismet/GameplayStatics.h"
#include "WorldSettings/IKGameModeBase.h"
#include "TimerManager.h"
#include "Components/DecalComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraComponent.h"

#include "Characters/Unit.h"
#include "Characters/EnemyBase.h"
#include "Components/CharacterStatComponent.h"

ADPI_LaserBeam::ADPI_LaserBeam()
	: fire_range_material_(nullptr), laser_niagara_system_(nullptr), fire_range_decal_(nullptr), laser_niagara_component_(nullptr), fire_rate_(0.5f), fire_range_(1000), damage_(1), movement_speed_reduction_amount_(-0.2f)
{
	PrimaryActorTick.bCanEverTick = true;
	is_periodic_ = false;

	laser_niagara_component_ = CreateDefaultSubobject<UNiagaraComponent>(TEXT("LaserNiagaraComponent"));
	laser_niagara_component_->Deactivate();
	laser_niagara_component_->SetupAttachment(RootComponent);

	fire_range_decal_ = CreateDefaultSubobject<UDecalComponent>(TEXT("Decal"));
	fire_range_decal_->SetupAttachment(RootComponent);
	fire_range_decal_->SetRelativeRotation(FRotator(90.0, 0.0, 0.0));
	fire_range_decal_->SetMobility(EComponentMobility::Movable);
	fire_range_decal_->DecalSize = FVector(1000, fire_range_, fire_range_);
}

void ADPI_LaserBeam::BeginPlay()
{
	Super::BeginPlay();

	fire_range_decal_->AttachToComponent(laser_niagara_component_, FAttachmentTransformRules::KeepRelativeTransform);

	if (fire_range_material_)
	{
		fire_range_decal_->SetDecalMaterial(fire_range_material_);
	}
	if (laser_niagara_system_)
	{
		laser_niagara_component_->SetAsset(laser_niagara_system_);
	}

	GetWorldTimerManager().SetTimer(fire_timer_handle_, this, &ADPI_LaserBeam::FireLaserBeam, fire_rate_, true);
}

void ADPI_LaserBeam::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorldTimerManager().ClearTimer(fire_timer_handle_);
}

void ADPI_LaserBeam::StartPassiveSkill()
{
	Super::StartPassiveSkill();
}

void ADPI_LaserBeam::Tick(float DeltaTime)
{
	if (IsValid(nearest_unit_))
	{
		if (!laser_niagara_component_->IsActive())
		{
			laser_niagara_component_->Activate(true);
		}
		laser_niagara_component_->SetVariableVec3(TEXT("Beam End"), nearest_unit_->GetActorLocation() - GetActorLocation());
	}
	else
	{
		if (laser_niagara_component_->IsActive())
		{
			laser_niagara_component_->SetVariableVec3(TEXT("Beam End"), FVector());
			laser_niagara_component_->DeactivateImmediate();
		}
	}
}

void ADPI_LaserBeam::FireLaserBeam()
{
	FVector location = GetActorLocation();

	UWorld* world = GetWorld();
	const float fire_range_squared = fire_range_ * fire_range_;

	if (world)
	{
		AIKGameModeBase* game_mode = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(world));
		TArray<AEnemyBase*> enemy_actors = game_mode->GetEnemyContainers();
		AActor* nearest_actor = nullptr;
		float nearest_distance_squared = FLT_MAX;
		for (AEnemyBase* actor : enemy_actors)
		{
			FVector to_actor = actor->GetActorLocation() - location;

			// Do not consider Z component to calculate distance.
			to_actor.Z = 0.f;

			float distance_squared_to_actor = to_actor.SizeSquared();
			if (distance_squared_to_actor <= fire_range_squared && distance_squared_to_actor <= nearest_distance_squared)
			{
				nearest_actor = actor;
				nearest_distance_squared = distance_squared_to_actor;
			}
		}
		
		// Cleanup pre-targeted unit
		if (IsValid(nearest_unit_))
		{
			nearest_unit_->RemoveBuff(TEXT("LaserMovementReduction"));
		}

		// Fire laser beam
		// Reduce movement speed
		nearest_unit_ = Cast<AUnit>(nearest_actor);
		if (nearest_unit_)
		{
			// @@ TODO: Set attacker
			FDamageData data = {damage_, EDamageType::Projectile, nullptr};
			nearest_unit_->GetDamage(data);
			nearest_unit_->ApplyBuff(FBuff(TEXT("LaserMovementReduction"), ECharacterStatType::MoveSpeed, movement_speed_reduction_amount_, true, true));
		}
	}
}
