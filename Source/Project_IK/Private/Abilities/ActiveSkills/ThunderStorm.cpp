/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 04.19.2025
Summary : Source file for an actor class for ThunderStorm.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/ActiveSkills/ThunderStorm.h"

#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "Sound/SoundCue.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "Components/DecalComponent.h"

#include "WorldSettings/IKGameModeBase.h"
#include "WorldSettings/IKPostProcessVolume.h"
#include "Structs/DamageData.h"

#include "Characters/Unit.h"
#include "Components/CharacterStatComponent.h"

#include "Subsystems/AudioManagerSubsystem.h"
#include "Components/AudioComponent.h"

// Sets default values
AThunderStorm::AThunderStorm()
{
	PrimaryActorTick.bCanEverTick = false;


	decal_ = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));
	decal_->SetupAttachment(RootComponent);
	decal_->SetRelativeRotation(FRotator(90.0, 0.0, 0.0));
}

void AThunderStorm::SetNecessaryData(float radius, float scaling_factor, float damage, AActor* skill_owner, float max_damage_count)
{
	radius_ = radius;
	decal_->DecalSize = FVector(radius);
	decal_->MarkRenderStateDirty();

	scaling_factor_ = scaling_factor;

	zap_damage_ = damage;

	skill_owner_ = skill_owner;

	max_storm_count_ = max_damage_count;
}

// Called when the game starts or when spawned
void AThunderStorm::BeginPlay()
{
	Super::BeginPlay();

	FindPostProcessVolume();
	BeginThunderStormPostProcess();

	if (visual_material_)
	{
		decal_->SetDecalMaterial(visual_material_);
	}

	GetWorld()->GetTimerManager().SetTimer(
		damage_handler_,
		this,
		&AThunderStorm::DamageEnemies,
		gap_between_damages_,
		true,
		first_delay_
	);

	environmental_audio_component_ = UAudioManagerSubsystem::Get(this)->PlayAttached(EAudioType::ThunderStormEnvironmental, decal_);
}

void AThunderStorm::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	EndThunderStormPostProcess();
	Super::EndPlay(EndPlayReason);
}

void AThunderStorm::DamageEnemies()
{
	storm_damage_count_ += 1;

	float squared_radius = radius_ * radius_;
	FVector storm_location = GetActorLocation();
	bool is_zap_spawned = false;

	UWorld* world = GetWorld();
	AIKGameModeBase* game_mode = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(world));
	if (game_mode)
	{
		const TArray<AActor*> enemies = game_mode->GetEnemyContainers();
		for (AActor* enemy : enemies)
		{
			FVector enemy_location = enemy->GetActorLocation();
			FVector to_actor = enemy_location - storm_location;

			AUnit* unit = Cast<AUnit>(enemy);
			if (unit)
			{
				enemy_location = enemy_location + unit->GetMesh()->GetRelativeLocation();
			}

			float squared_distance_to_actor = to_actor.SizeSquared();
			if (squared_distance_to_actor <= squared_radius)
			{
				ApplyDamage({ 0.f, zap_damage_, EDamageType::Magic, skill_owner_, enemy });
				SpawnVFX(world, enemy_location);
				is_zap_spawned = true;
			}
		}
	}

	if (is_zap_spawned)
	{
		SpawnSFX(world, storm_location);
	}

	if (int32 fade_count = max_storm_count_ - 1;
		storm_damage_count_ == fade_count)
	{
		if (environmental_audio_component_)
		{
			environmental_audio_component_->FadeOut(gap_between_damages_, 0.f);
		}
	}

	if (storm_damage_count_ >= max_storm_count_)
	{
		world->GetWorld()->GetTimerManager().ClearTimer(damage_handler_);
		Destroy();
	}
}

void AThunderStorm::ApplyDamage(FDamageData DamageData)
{
	AUnit* attack_target = Cast<AUnit>(DamageData.attack_target_);

	if (DamageData.attacker_.IsValid() && DamageData.attacker_->IsA<AUnit>())
	{
		AUnit* attacker = Cast<AUnit>(DamageData.attacker_);
		DamageData.skill_power_base_dmg_ = DamageData.skill_power_base_dmg_ + (attacker->GetCharacterStat()->GetSkillPower() * scaling_factor_);
	}

	attack_target->GetDamage(DamageData);
}

void AThunderStorm::SpawnSFX(UWorld* world, const FVector& location)
{
	GetGameInstance()->GetSubsystem<UAudioManagerSubsystem>()->PlayAtLocation(EAudioType::ThunderZap, location);
}

void AThunderStorm::SpawnVFX(UWorld* world, const FVector& location)
{
	UNiagaraSystem* system = zap_particle_.Get();
	if (system)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(world, system, location);
	}
}

void AThunderStorm::FindPostProcessVolume()
{
	// Search for any PostProcessVolume in the level
	for (TActorIterator<AIKPostProcessVolume> it(GetWorld()); it; ++it)
	{
		AIKPostProcessVolume* found_volume = *it;
		if (found_volume && found_volume->IsValidLowLevel())
		{
			post_process_volume_ = found_volume;
			break;
		}
	}
}

void AThunderStorm::BeginThunderStormPostProcess()
{
	AIKPostProcessVolume* ppv = post_process_volume_.Get();
	if (ppv)
	{
		ppv->BeginThunderStorm();
	}
}

void AThunderStorm::EndThunderStormPostProcess()
{
	AIKPostProcessVolume* ppv = post_process_volume_.Get();
	if (ppv)
	{
		ppv->EndThunderStorm();
	}
}
