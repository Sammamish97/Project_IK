/******************************************************************************
Copyright(C) 2025
Author: Sinil Kang (rtd99062@gmail.com)
Creation Date : 6.29.2025
Summary : Struct file for EnemySpawnData.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "DataAssets/EnemySpawnUnitAsset.h"
#include "EnemySpawnData.generated.h"



USTRUCT(BlueprintType)
struct PROJECT_IK_API FEnemySpawnData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UEnemySpawnUnitAsset* enemy_spawn_unit_array_;
};
