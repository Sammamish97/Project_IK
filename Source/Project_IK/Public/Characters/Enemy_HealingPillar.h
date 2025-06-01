/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.18.2025
Summary : Header file for Healing Pillar.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Enemy_PillarBase.h"
#include "Enemy_HealingPillar.generated.h"

UCLASS(Abstract)
class PROJECT_IK_API AEnemy_HealingPillar : public AEnemy_PillarBase
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy_HealingPillar();
	virtual void ActivateBuff() override;

private:
	float heal_amount_ = 100.f;
};
