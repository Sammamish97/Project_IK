/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 02.27.2025
Summary : Source file for manager that controls spawning enemies.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Managers/EnemySpawnerManager.h"

#include "Abilities/Buffs/BuffHandler.h"
#include "Characters/EnemyBase.h"
#include "Kismet/GameplayStatics.h"
#include "WorldSettings/IKPlayerController.h"

#include "DataAssets/EnemySpawnDataAsset.h"
#include "WorldSettings/IKHUD.h"

#include "WorldSettings/IKGameInstance.h"
#include "UI/Map/IKMaps.h"

UEnemySpawnerManager::UEnemySpawnerManager()
	:spawn_distance_(), enemy_waves_(0), spawn_position_(), enemy_spacing_(300)
{
}

void UEnemySpawnerManager::Initialize(FVector base_spawn_position)
{
	spawn_position_ = base_spawn_position;


	int32 path_num = Cast<UIKGameInstance>(GetWorld()->GetGameInstance())->GetMapPtr()->GetPlayerVisitedPath().Num();

	if (path_num < 5)
	{
		enemy_waves_ = 2;
		spawn_data_ptr_ = enemy_spawn_data_asset_early_;
	}
	else if(path_num < 10)
	{
		enemy_waves_ = 3;
		spawn_data_ptr_ = enemy_spawn_data_asset_mid_;
	}
	else
	{
		enemy_waves_ = 4;
		spawn_data_ptr_ = enemy_spawn_data_asset_late_;
	}

	//Test Perpose
	if (revenge_buff_ ==nullptr)
	{
		revenge_buff_ = NewObject<UBuffHandler>(this, revenge_buff_class_);
	}
	if (unity_buff_ ==nullptr)
	{
		unity_buff_ = NewObject<UBuffHandler>(this, unity_buff_class_);
	}
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

	if (spawn_data_ptr_ == nullptr)
	{
		spawn_data_ptr_ = enemy_spawn_data_asset_early_;
	}
	FEnemySpawnData enemy_spawn_data = spawn_data_ptr_->GetRandomEnemySpawnData();
	for (const FEnemySpawnUnit& unit : enemy_spawn_data.enemy_spawn_unit_array_->spawn_units_)
	{
		FActorSpawnParameters param;
		param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		param.bNoFail = true;

		AEnemyBase* enemy = GetWorld()->SpawnActor<AEnemyBase>(unit.enemy_class_, spawn_position_ + unit.spawn_offset_, FRotator::ZeroRotator, param);
		if (enemy)
		{
			enemies_.Add(enemy);
		}
	}
	//Test Perpose. 나중에 회차 후반부, 랜덤한 유닛에게 이런식으로 버프를 걸어야 한다.
	for (const auto& elem : enemies_)
	{
		unity_buff_->ApplyBuff(Cast<AUnit>(elem));
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

void UEnemySpawnerManager::RemoveAllEnemy()
{
	for (AActor* actor : enemies_)
	{
		actor->Destroy();
	}
	enemies_.Empty();
	enemy_waves_ = 0;
}

bool UEnemySpawnerManager::IsEnemyAllDefeated()
{
	return enemies_.Num() <= 0 && enemy_waves_ <= 0;
}
