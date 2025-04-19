/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.03.2024
Summary : Header file for Bullet.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Structs/DamageData.h"
#include "Weapons/PooledActor.h"
#include "Bullet.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
UCLASS(Abstract)
class PROJECT_IK_API ABullet : public APooledActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void SetShooter(TWeakObjectPtr<AActor> shooter);

	UFUNCTION()
	void SetDamageData(FDamageData data);
	void SetCollisionPreset(bool is_hero);

	UFUNCTION()
	void AddOnHitComponent(TSubclassOf<class UBulletOnHitEffectComponent> target_component);
	void RemoveOnHitComponent(TSubclassOf<class UBulletOnHitEffectComponent> target_component);
	void ClearOnHitComponents();

	virtual void SetInUse(bool in_use) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bullet", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USphereComponent> collision_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, BlueprintReadWrite, Category = "Bullet", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UProjectileMovementComponent> movement_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bullet", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> bullet_mesh_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bullet", meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UBulletOnHitEffectComponent>> on_hit_components_;

	UPROPERTY(VisibleAnywhere, Category = "Bullet")
	TWeakObjectPtr<AActor> shooter_;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Bullet", meta = (AllowPrivateAccess = "true"))
	FDamageData dmg_data_;
};
