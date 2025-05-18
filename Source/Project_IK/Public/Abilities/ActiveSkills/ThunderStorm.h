/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 04.19.2025
Summary : Header file for an actor class for ThunderStorm.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ThunderStorm.generated.h"


class UNiagaraSystem;
class UNiagaraComponent;
class USoundCue;
struct FDamageData;
class AIKPostProcessVolume;

UCLASS()
class PROJECT_IK_API AThunderStorm : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AThunderStorm();

	UFUNCTION(BlueprintCallable)
	void SetNecessaryData(float radius, float scaling_factor, float damage, AActor* skill_owner);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	TArray<TObjectPtr<USoundCue>> zap_sound_cue_array_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	TObjectPtr<UNiagaraSystem> zap_particle_ = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Visuals")
	TObjectPtr<UMaterialInterface> visual_material_ = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason);

	void DamageEnemies();
	void ApplyDamage(FDamageData DamageData);
	void SpawnSFX(UWorld* world, const FVector& location);
	void SpawnVFX(UWorld* world, const FVector& location);

	void FindPostProcessVolume();
	void BeginThunderStormPostProcess();
	void EndThunderStormPostProcess();

	UPROPERTY()
	TObjectPtr<UAudioComponent> zap_sfx_component_ = nullptr;
	UPROPERTY()
	TObjectPtr<UNiagaraComponent> zap_vfx_component_ = nullptr;
	UPROPERTY()
	TObjectPtr<UDecalComponent> decal_ = nullptr;

	int32 storm_damage_count_ = 0;
	FTimerHandle damage_handler_;
	float radius_ = 0.f;
	float scaling_factor_ = 0.f;
	float zap_damage_ = 0.f;
	TWeakObjectPtr<AActor> skill_owner_;

	TWeakObjectPtr<AIKPostProcessVolume> post_process_volume_;
};
