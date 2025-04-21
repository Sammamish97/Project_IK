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

UCLASS()
class PROJECT_IK_API AShockJavelin : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AShockJavelin();

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ShockJavelin", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UBoxComponent> collision_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, BlueprintReadWrite, Category = "ShockJavelin", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UProjectileMovementComponent> movement_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ShockJavelin", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> javelin_mesh_;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "ShockJavelin", meta = (AllowPrivateAccess = "true"))
	FDamageData dmg_data_;

	float cover_dmg_scale_ = 3.f;
	float stun_duration_ = 2.f;
};
