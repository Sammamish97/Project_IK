/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 02.27.2025
Summary : Source file for manager that controls spawning enemies.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Managers/EnemySpawnerManager.h"

#include "Characters/EnemyBase.h"
#include "Components/CharacterStatComponent.h"

#include "Kismet/GameplayStatics.h"
#include "WorldSettings/IKGameInstance.h"
#include "WorldSettings/IKPlayerController.h"
#include "Managers/DataTableManager.h"

#include "DataAssets/EnemySpawnDataAsset.h"

UEnemySpawnerManager::UEnemySpawnerManager()
	:spawn_distance_(), enemy_waves_(0), spawn_position_(), enemy_spacing_(300)
{
}

void UEnemySpawnerManager::Initialize(FVector base_spawn_position, int32 waves)
{
	spawn_position_ = base_spawn_position;
	enemy_waves_ = waves;
}

void UEnemySpawnerManager::SpawnEnemies()
{
	if (enemy_waves_ <= 0)
	{
		return;
	}

	enemy_waves_ -= 1;

	// Get hero spawn data
	// Spawn enemies in a distance from the point.
	spawn_position_ += spawn_distance_;

	FEnemySpawnData enemy_spawn_data = enemy_spawn_data_asset_->GetRandomEnemySpawnData();
	for (const FEnemySpawnUnit& unit : enemy_spawn_data.enemy_spawn_unit_array_->spawn_units_)
	{
		AEnemyBase* enemy = GetWorld()->SpawnActor<AEnemyBase>(unit.enemy_class_, spawn_position_ + unit.spawn_offset_, FRotator::ZeroRotator);
		if (enemy)
		{
			enemies_.Add(enemy);
		}
	}

	AIKPlayerController* pc = Cast<AIKPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (pc)
	{
		pc->UpdateEnemies(enemies_);
	}
}

const TArray<TObjectPtr<AActor>>& UEnemySpawnerManager::GetEnemies()
{
	return enemies_;
}

void UEnemySpawnerManager::RemoveEnemy(AEnemyBase* enemy_defeated)
{
	enemies_.Remove(enemy_defeated);
	if (enemies_.IsEmpty())
	{
		SpawnEnemies();
	}
}

//치트 코드 용 함수.
void UEnemySpawnerManager::RemoveAllEnemy()
{
	enemies_.Empty();
	enemy_waves_ = 0;
}

bool UEnemySpawnerManager::IsEnemyAllDefeated()
{
	return enemies_.Num() <= 0 && enemy_waves_ <= 0;
}
