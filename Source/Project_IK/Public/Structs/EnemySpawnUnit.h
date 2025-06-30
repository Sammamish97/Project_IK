/******************************************************************************
Copyright(C) 2025
Author: Sinil Kang (rtd99062@gmail.com)
Creation Date : 6.29.2025
Summary : Struct file for EnemySpawnUnit.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "EnemySpawnUnit.generated.h"

class AEnemyBase;

USTRUCT(BlueprintType)
struct PROJECT_IK_API FEnemySpawnUnit
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AEnemyBase> enemy_class_;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FVector spawn_offset_;
};