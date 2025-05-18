/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.18.2025
Summary : Header file for Pillar Base.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "EnemyBase.h"
#include "Enemy_PillarBase.generated.h"

UCLASS(Abstract)
class PROJECT_IK_API AEnemy_PillarBase : public AEnemyBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy_PillarBase();
	virtual void BeginPlay() override;
	virtual void ActivateBuff();

protected:
	FTimerHandle buff_timer_;
	float buff_term_ = 5;
	float buff_range_ = 1000;
};
