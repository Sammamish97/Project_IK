/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 11.10.2024
Summary : Source file for managing trasition between levels.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Subsystems/LevelTransitionSubsystem.h"

#include "Subsystems/GlobalBuffSubsystem.h"
#include "WorldSettings/IKGameInstance.h"
#include "Structs/SpawnData.h"
#include "Kismet/GameplayStatics.h"
#include "UI/IKMaps.h"

class UIKGameInstance;

void ULevelTransitionSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
}

void ULevelTransitionSubsystem::Deinitialize()
{
	Super::Deinitialize();
}

void ULevelTransitionSubsystem::UpdateSpawnData(const TArray<FSpawnData>& data)
{
	spawn_data_.Empty();
	for(auto elem : data)
	{
		spawn_data_.Add(elem);
	}
}

void ULevelTransitionSubsystem::UpdateSpawnDataIdx(int32 idx, FSpawnData data)
{
	if (spawn_data_.Num() < idx)
	{
		UE_LOG(LogTemp, Error, TEXT("SpawnData is out of range"));
	}
	spawn_data_[idx] = data;
}

void ULevelTransitionSubsystem::OpenLevel(UWorld* world, FIntPoint map_position)
{
	UIKGameInstance* instance = Cast<UIKGameInstance>(GetGameInstance());
	instance->GetSubsystem<UGlobalBuffSubsystem>()->UpdateBuffDurations();
	FMapNode node = instance->GetMapPtr()->GetNode(map_position.X, map_position.Y);
	instance->GetMapPtr()->SetPlayerGridPosition(map_position);
	switch (node.type)
	{
	case NodeType::None:
		UE_LOG(LogTemp, Warning, TEXT("ULevelTransitionManager::OpenLevel -> Tried to go to invalid map node"));
		break;
	case NodeType::Enemy:
		UGameplayStatics::OpenLevel(world, FName("CombatLevel"));
		break;
	case NodeType::Merchant:
		UGameplayStatics::OpenLevel(world, FName("StoreLevel"));
		break;
	case NodeType::Event:
		UGameplayStatics::OpenLevel(world, FName("EventLevel"));
		break;
	case NodeType::Boss:
		UGameplayStatics::OpenLevel(world, FName("BossLevel"));
		break;
	default:
		break;
	}
}

const TArray<FSpawnData>& ULevelTransitionSubsystem::GetSpawnData() const
{
	return spawn_data_;
}

FSpawnData ULevelTransitionSubsystem::GetSpawnData(int32 idx) const
{
	return spawn_data_[idx];
}