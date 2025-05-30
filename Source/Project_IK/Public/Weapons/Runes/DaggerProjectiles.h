/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 05.30.2025
Summary : Header file for dagger projectiles.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Weapons/Guns/Bullet.h"
#include "DaggerProjectiles.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API ADaggerProjectiles : public ABullet
{
	GENERATED_BODY()
public:
	ADaggerProjectiles();

	void BeginDaggerMovements();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dagger Times")
	float summon_times_ = 0.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Dagger Times")
	float backward_times_ = 0.1f;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void StartBackwardMotion();

	UFUNCTION()
	void LaunchForward();

	FTimerHandle dagger_timer_;
	float init_speed_ = 0.f;
};
