/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.18.2025
Summary : Header file for Laser drone enemy.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "Enemy_LaserDrone.generated.h"

UCLASS(Abstract)
class PROJECT_IK_API AEnemy_LaserDrone : public AEnemyBase
{
	GENERATED_BODY()

public:
	AEnemy_LaserDrone();
	float GetLaserRange() const;

	virtual void BeginPlay() override;
protected:
	virtual void Attack(AActor* target) override;

private:
	float laser_damage_ = 5.f;
	float laser_range_ = 600.f;
	FName muzzle_socket_name = FName("muzzle");
};
