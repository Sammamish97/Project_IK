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

// Sets default values
AThunderStorm::AThunderStorm()
{
	PrimaryActorTick.bCanEverTick = false;


	decal_ = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));
	decal_->SetupAttachment(RootComponent);
	decal_->SetRelativeRotation(FRotator(90.0, 0.0, 0.0));
}

void AThunderStorm::SetNecessaryData(float radius, float scaling_factor, float damage, AActor* skill_owner)
{
	radius_ = radius;
	decal_->DecalSize = FVector(radius);
	decal_->MarkRenderStateDirty();

	scaling_factor_ = scaling_factor;

	zap_damage_ = damage;

	skill_owner_ = skill_owner;
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
		0.5f,
		true,
		1.f
	);
}

void AThunderStorm::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	EndThunderStormPostProcess();
	zap_sound_cue_array_.Empty();
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

	if (storm_damage_count_ >= 4)
	{
		world->GetWorld()->GetTimerManager().ClearTimer(damage_handler_);
		Destroy();
	}
}

void AThunderStorm::ApplyDamage(FDamageData DamageData)
{
	AUnit* attack_target = Cast<AUnit>(DamageData.attack_target);

	if (DamageData.attacker.IsValid() && DamageData.attacker->IsA<AUnit>())
	{
		AUnit* attacker = Cast<AUnit>(DamageData.attacker);
		DamageData.skill_power_base_dmg = DamageData.skill_power_base_dmg + (attacker->GetCharacterStat()->GetSkillPower() * scaling_factor_);
	}

	attack_target->GetDamage(DamageData);
}

void AThunderStorm::SpawnSFX(UWorld* world, const FVector& location)
{
	int32 rand_sound_index = FMath::RandRange(0, zap_sound_cue_array_.Num() - 1);
	if (zap_sound_cue_array_.IsValidIndex(rand_sound_index))
	{
		USoundCue* sound = zap_sound_cue_array_[rand_sound_index].Get();
		if (sound)
		{
			UGameplayStatics::PlaySoundAtLocation(world, sound, location);
		}
	}
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
