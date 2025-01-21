/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 11.10.2024
Summary : Header file for managing trasition between levels.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "EnumCluster.h"

#include "LevelTransitionManager.generated.h"


struct FCharacterData;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API ULevelTransitionManager : public UObject
{
	GENERATED_BODY()
public:
	ULevelTransitionManager();

	UFUNCTION()
	void SetInstanceCache(UGameInstance* game_instance);
	
	UFUNCTION(BlueprintCallable)
	void InitHeroData(const TArray<EHeroType>& hero_types);

	UFUNCTION(BlueprintCallable)
	void OpenLevel(UWorld* world, FIntPoint map_position);
	
	// Function be called in GameMode::BeginPlay
	UFUNCTION(BlueprintCallable)
	void PrepareLevel(UWorld* world);

	UFUNCTION(BlueprintCallable)
	void SetActorBlueprints(TSubclassOf<AActor> hero_blueprint, TSubclassOf<AActor> enemy_blueprint);

	UFUNCTION(BlueprintCallable)
	const TArray<FCharacterData>& GetSavedData() const;

	FCharacterData GetSavedData(int idx) const;

	UFUNCTION(BlueprintCallable)
	void SetHeroPeriodicDPData(EDPType type, int idx);

	UFUNCTION(BlueprintCallable)
	void SetHeroGenericDPData(EDPType type, int idx);
	

protected:
	void SpawnHeroes(UWorld* world);
	void SpawnEnemies(UWorld* world);

	void SaveData(UWorld* world);

	UPROPERTY()
	UGameInstance* instance_cache_;
	
	UPROPERTY()
	TArray<FCharacterData> data_;

	UPROPERTY()
	TSubclassOf<AActor> enemy_blueprint_;
};
