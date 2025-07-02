/******************************************************************************
Copyright(C) 2025
Author: Sinil Kang (rtd99062@gmail.com)
Creation Date : 6.29.2025
Summary : Header file for a data asset that manages EnemySpawnData.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Structs/EnemySpawnData.h"
#include "EnemySpawnDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UEnemySpawnDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	const FEnemySpawnData& GetRandomEnemySpawnData() const;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FEnemySpawnData> enemy_spawn_data_;
};
