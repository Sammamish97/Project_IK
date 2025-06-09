/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.18.2025
Summary : Header file for Shock Javelin.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Structs/DamageData.h"
#include "ShockJavelin.generated.h"

class UNiagaraSystem;
class UNiagaraComponent;

UCLASS(Abstract)
class PROJECT_IK_API AShockJavelin : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AShockJavelin();
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SetDamageData(const FDamageData& dmg_data);
	void SetCastingTime(float casting_time);

protected:
	virtual void BeginPlay();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ShockJavelin")
	TObjectPtr<class UBoxComponent> collision_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, BlueprintReadWrite, Category = "ShockJavelin")
	TObjectPtr<class UProjectileMovementComponent> movement_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ShockJavelin")
	TObjectPtr<UNiagaraComponent> particle_system_;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "ShockJavelin")
	FDamageData dmg_data_;

	float cover_dmg_scale_ = 3.f;
	float stun_duration_ = 2.f;

	float casting_time_ = 0.f;
	float timer_ = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float javelin_length_ = 300.f;
	bool has_dispatched_ = false;
};
