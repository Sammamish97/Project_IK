/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.22.2025
Summary : Header file for Mini Bullet.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Structs/DamageData.h"
#include "MiniBullet.generated.h"

UCLASS()
class PROJECT_IK_API AMiniBullet : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMiniBullet();

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SetDamageData(FDamageData dmg_data);
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ShockJavelin", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UBoxComponent> collision_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, BlueprintReadWrite, Category = "ShockJavelin", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UProjectileMovementComponent> movement_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ShockJavelin", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UStaticMeshComponent> mesh_;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "ShockJavelin", meta = (AllowPrivateAccess = "true"))
	FDamageData dmg_data_;
};
