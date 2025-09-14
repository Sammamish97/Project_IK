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
#include "EnemySpawnerManager.generated.h"

class UWorld;
class AEnemyBase;
class UEnemySpawnDataAsset;
class UBuffHandler;

UCLASS(Blueprintable)
class PROJECT_IK_API UEnemySpawnerManager : public UObject
{
	GENERATED_BODY()
public:
	UEnemySpawnerManager();

	void Initialize(FVector base_spawn_position);

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemySpawner")
	TObjectPtr<UEnemySpawnDataAsset> enemy_spawn_data_asset_early_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemySpawner")
	TObjectPtr<UEnemySpawnDataAsset> enemy_spawn_data_asset_mid_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemySpawner")
	TObjectPtr<UEnemySpawnDataAsset> enemy_spawn_data_asset_late_;

	UEnemySpawnDataAsset* spawn_data_ptr_ = nullptr;
	
	//Test Perpose
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UBuffHandler> revenge_buff_class_;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UBuffHandler> unity_buff_class_;

	UPROPERTY(Transient)
	TObjectPtr<UBuffHandler> revenge_buff_;

	UPROPERTY(Transient)
	TObjectPtr<UBuffHandler> unity_buff_;
	//
};
