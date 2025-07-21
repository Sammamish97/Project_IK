/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 07.12.2025
Summary : Header file for an actor of charge shot skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Structs/DamageData.h"
#include "GameFramework/Actor.h"
#include "ChargeShot.generated.h"

class UBoxComponent;
class UProjectileMovementComponent;
class UNiagaraSystem;
class UNiagaraComponent;

UCLASS()
class PROJECT_IK_API AChargeShot : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AChargeShot();
	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SetDamageData(const FDamageData& dmg_data);
	void SetCastingTime(float casting_time);

protected:
	virtual void BeginPlay();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ChargeShot")
	TObjectPtr<UBoxComponent> collision_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, BlueprintReadWrite, Category = "ChargeShot")
	TObjectPtr<UProjectileMovementComponent> movement_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ChargeShot")
	TObjectPtr<UNiagaraComponent> particle_system_;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "ChargeShot")
	FDamageData dmg_data_;

	float casting_time_ = 0.f;
	float timer_ = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float charge_shot_length_ = 300.f;
	bool has_dispatched_ = false;
};
