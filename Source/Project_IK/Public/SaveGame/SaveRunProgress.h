/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.09.2025
Summary : Header file for SaveGame that saves data about combat run.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "SaveGame/BaseSaveGame.h"
#include "Structs/SpawnData.h"
#include "SaveRunProgress.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API USaveRunProgress : public UBaseSaveGame
{
	GENERATED_BODY()
	
public:
	// Map
	UPROPERTY(VisibleAnywhere)
	int32 rand_seed_for_map_;
	UPROPERTY(VisibleAnywhere)
	int32 map_height_;		// May be changed if map size has determined by a loop stage
	UPROPERTY(VisibleAnywhere)
	int32 map_width_;		// May be changed if map size has determined by a loop stage
	UPROPERTY(VisibleAnywhere)
	TArray<FIntPoint> player_visited_path_;


	// Hero status
	UPROPERTY(VisibleAnywhere)
	TMap<EHeroType, FSpawnData> spawn_data_;

	UPROPERTY(VisibleAnywhere)
	int32 credits_;
	
	// Global buffs type & duration
	UPROPERTY(VisibleAnywhere)
	TMap<EGlobalBuffType, int32> applied_global_buffs_;		// Need to check recovering worked by adding buffs

	// Random seed
	UPROPERTY(VisibleAnywhere)
	int32 rand_seed_;

	// Tutorial for once
	UPROPERTY(VisibleAnywhere, SaveGame)
	bool is_first_battle_ = true;

	UPROPERTY(VisibleAnywhere, SaveGame)
	bool is_first_inventory_ = true;
};
