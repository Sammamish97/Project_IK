/******************************************************************************
Copyright(C) 2025
Author: Sinil Kang (rtd99062@gmail.com)
Creation Date : 6.29.2025
Summary : Header file for a data asset that manages EnemySpawnUnit.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Structs/EnemySpawnUnit.h"
#include "EnemySpawnUnitAsset.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UEnemySpawnUnitAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FEnemySpawnUnit> spawn_units_;
};
