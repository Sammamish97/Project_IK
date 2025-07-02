/******************************************************************************
Copyright(C) 2025
Author: Sinil Kang (rtd99062@gmail.com)
Creation Date : 6.29.2025
Summary : Source file for a data asset that manages EnemySpawnData.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "DataAssets/EnemySpawnDataAsset.h"

const FEnemySpawnData& UEnemySpawnDataAsset::GetRandomEnemySpawnData() const
{
	int32 rand_index = FMath::RandRange(0, enemy_spawn_data_.Num() - 1);
	return enemy_spawn_data_[rand_index];
}
