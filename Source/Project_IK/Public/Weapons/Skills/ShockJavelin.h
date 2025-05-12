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

UCLASS(Abstract)
class PROJECT_IK_API AShockJavelin : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AShockJavelin();

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SetDamageData(FDamageData dmg_data);
	
protected:
	virtual void BeginPlay();
	void BeginCooling();

	UFUNCTION()
	void Cooling();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ShockJavelin", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UBoxComponent> collision_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, BlueprintReadWrite, Category = "ShockJavelin", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UProjectileMovementComponent> movement_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ShockJavelin", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> javelin_mesh_;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "ShockJavelin", meta = (AllowPrivateAccess = "true"))
	FDamageData dmg_data_;

	TWeakObjectPtr<UMaterialInstanceDynamic> dynamic_material_instance_;

	float cover_dmg_scale_ = 3.f;
	float stun_duration_ = 2.f;

	FTimerHandle cooling_timer_;
	float cooling_alpha_ = 0.f;
	static constexpr float cooling_step_ = 0.01f;
	FLinearColor init_emissive_ = FLinearColor::Transparent;
};
