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


UEnemySpawnerManager::UEnemySpawnerManager()
	:spawn_distance_(), enemy_waves_(0), spawn_position_(), enemy_spacing_(300), enemy_num_(1)
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

	float half_enemy_height = 90.f;
	if (enemy_class_)
	{
		AEnemyBase* default_enemy = enemy_class_->GetDefaultObject<AEnemyBase>();
		if (default_enemy)
		{
			UStaticMeshComponent* static_mesh_component = default_enemy->FindComponentByClass<UStaticMeshComponent>();
			if (static_mesh_component && static_mesh_component->GetStaticMesh())
			{
				half_enemy_height = static_mesh_component->GetStaticMesh()->GetBoundingBox().GetExtent().Z;
			}
			else 
			{
				USkeletalMeshComponent* skeletal_mesh_component = default_enemy->FindComponentByClass<USkeletalMeshComponent>();
				if (skeletal_mesh_component && skeletal_mesh_component->GetSkeletalMeshAsset())
				{
					half_enemy_height = skeletal_mesh_component->GetSkeletalMeshAsset()->GetBounds().BoxExtent.Z;
				}
			}
		}
	}

	for (int32 i = 0; i < enemy_num_; i++)
	{
		FVector spawn_offset = FVector(0.f, (enemy_spacing_ * (enemy_num_ - 1) / -2.f) + (i * enemy_spacing_), half_enemy_height);
		// It may return nullptr if enemy_spacing_ is too narrow.
		AEnemyBase* enemy = GetWorld()->SpawnActor<AEnemyBase>(enemy_class_, spawn_position_ + spawn_offset, FRotator());
		if (enemy)
		{
			enemy->SpawnDefaultController();

			enemies_.Add(enemy);
		}
	}
}

const TArray<TObjectPtr<AEnemyBase>>& UEnemySpawnerManager::GetEnemies()
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
