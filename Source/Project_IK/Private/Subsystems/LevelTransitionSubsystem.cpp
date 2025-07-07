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

void ULevelTransitionSubsystem::UpdateSpawnData(const TMap<EHeroType, FSpawnData>& data)
{
	spawn_data_.Empty();
	spawn_data_ = data;
}

void ULevelTransitionSubsystem::UpdateSpawnDataIdx(EHeroType type, FSpawnData data)
{
	spawn_data_[type] = data;
}

void ULevelTransitionSubsystem::UpdateSupportSkillDataIdx(int32 idx, FSupportSkillData data)
{
	if (support_skill_data_.Num() < idx)
	{
		UE_LOG(LogTemp, Error, TEXT("Support Skill Data is out of range"));
	}
	support_skill_data_[idx] = data;
}

void ULevelTransitionSubsystem::UpdateSupportSkillData(const TArray<FSupportSkillData>& data)
{
	support_skill_data_.Empty();
	for(auto elem : data)
	{
		support_skill_data_.Add(elem);
	}
}

void ULevelTransitionSubsystem::OpenMapLevel(UWorld* world)
{
	UGameplayStatics::OpenLevel(world, FName("MapInventoryLevel"));
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

const TMap<EHeroType, FSpawnData>& ULevelTransitionSubsystem::GetSpawnData() const
{
	return spawn_data_;
}

FSpawnData ULevelTransitionSubsystem::GetSpawnData(EHeroType type) const
{
	return spawn_data_[type];
}
