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
#include "Subsystems/GameInstanceSubsystem.h"
#include "LevelTransitionSubsystem.generated.h"
UCLASS()
class PROJECT_IK_API ULevelTransitionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	
	UFUNCTION(BlueprintCallable)
	void InitHeroData(const TArray<EHeroType>& hero_types);

	UFUNCTION(BlueprintCallable)
	void OpenLevel(UWorld* world, FIntPoint map_position);
	
	// Function be called in GameMode::BeginPlay
	UFUNCTION(BlueprintCallable)
	void PrepareLevel(UWorld* world);
	
	UFUNCTION(BlueprintCallable)
	const TArray<FSpawnData>& GetSavedData() const;

	FSpawnData GetSavedData(int idx) const;

protected:
	void SpawnHeroes(UWorld* world);
	//void SpawnEnemies(UWorld* world);

	void SaveData(UWorld* world);
	
	UPROPERTY()
	TArray<FSpawnData> spawn_data_;
};
