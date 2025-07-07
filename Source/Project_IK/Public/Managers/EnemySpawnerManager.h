/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 02.27.2025
Summary : Header file for manager that controls spawning enemies.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EnemySpawnerManager.generated.h"

class UWorld;
class AEnemyBase;
class UEnemySpawnDataAsset;

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECT_IK_API UEnemySpawnerManager : public UObject
{
	GENERATED_BODY()
public:
	UEnemySpawnerManager();

	void Initialize(FVector base_spawn_position, int32 waves);

	void SpawnEnemies();

	const TArray<TObjectPtr<AActor>>& GetEnemies();

	void RemoveEnemy(AEnemyBase* enemy_defeated);
	void RemoveAllEnemy();

	bool IsEnemyAllDefeated();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemySpawner")
	FVector spawn_distance_;

	int32 enemy_waves_;

	FVector spawn_position_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemySpawner")
	int32 enemy_spacing_;
	
	// How strong enemies spawned?
	UPROPERTY(BlueprintReadWrite)
	TArray<TObjectPtr<AActor>> enemies_;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Status Info", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UEnemySpawnDataAsset> enemy_spawn_data_asset_;
};
