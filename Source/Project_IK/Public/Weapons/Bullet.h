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
#include "Weapons/PooledActor.h"
#include "Bullet.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
UCLASS()
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
	void SetDamage(float damage);
	void SetCollisionPreset(bool is_hero);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetInUse(bool in_use) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bullet", meta = (AllowPrivateAccess = "true", BindWidget))
	USphereComponent* collision_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, BlueprintReadWrite, Category = "Bullet", meta = (AllowPrivateAccess = "true", BindWidget))
	UProjectileMovementComponent* movement_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bullet", meta = (AllowPrivateAccess = "true", BindWidget))
	UStaticMeshComponent* bullet_mesh_;

	UPROPERTY(VisibleAnywhere, Category = "Bullet")
	TWeakObjectPtr<AActor> shooter_;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Bullet", meta = (AllowPrivateAccess = "true"))
	float damage_;
};
