/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 04.21.2025
Summary : Header file for an actor class for FateSpiral.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FateSpiral.generated.h"

class UNiagaraSystem;

UCLASS()
class PROJECT_IK_API AFateSpiral : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFateSpiral();

	void SetNecessaryData(AActor* skill_owner, AActor* departure, AActor* arrival, float radius, bool upgraded);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UNiagaraSystem> skill_particle_system_;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void ConductLogic();

	void HealAlly();
	void DamageEnemy();
	AActor* FindNextTarget();
	float GetOwnerSkillPower();

	void EndLogic();

	void SpawnVisualFX();
public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fate Spiral")
	float heal_amount_ = 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fate Spiral")
	float damage_amount_ = 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fate Spiral")
	float heal_scaling_factor_ = 0.4f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fate Spiral")
	float damage_scaling_factor_ = 0.6f;

protected:
	UPROPERTY()
	AActor* departure_ = nullptr;

	UPROPERTY()
	AActor* arrival_ = nullptr;
	
	int32 jump_count_ = 0;

	FTimerHandle fate_sprial_handler_;

	float owner_skill_power_ = 0.f;
	TWeakObjectPtr<AActor> skill_owner_cache_;

	float range_squared_ = FLT_MAX;

	UPROPERTY()
	TSet<AActor*> traversed_actors_;

	bool is_upgraded_ = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient)
	float traverse_interval_ = 0.5f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Transient)
	int32 maximum_traversals_ = 4;
};
