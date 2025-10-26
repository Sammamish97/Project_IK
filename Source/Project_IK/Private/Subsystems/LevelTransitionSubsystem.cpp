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
#include "UI/Map/IKMaps.h"
#include "Managers/DataTableManager.h"

class UIKGameInstance;

void ULevelTransitionSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	ClearSpawnData();
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

void ULevelTransitionSubsystem::OpenLevel(UWorld* world, ELevelState state)
{
	switch (state)
	{
	case ELevelState::MainMenuLevel:
		UGameplayStatics::OpenLevel(world, FName("MainMenuLevel"));
		break;

	case ELevelState::LobbyLevel:
		UGameplayStatics::OpenLevel(world, FName("LobbyLevel"));
		break;

	case ELevelState::GotchaLevel:
		UGameplayStatics::OpenLevel(world, FName("GotchaLevel"));
		break;

	case ELevelState::MapLevel:
		UGameplayStatics::OpenLevel(world, FName("MapInventoryLevel"));
		break;

	case ELevelState::Opening:
		UGameplayStatics::OpenLevel(world, FName("/Game/_Scenes/Opening"));
		break;

	case ELevelState::Ending:
		UGameplayStatics::OpenLevel(world, FName("Ending"));
		break;

	default:
		checkNoEntry();
	}
}

void ULevelTransitionSubsystem::HealHeroesSpawnDataPercentage(float heal_percentage)
{
	if (heal_percentage <= 0.f)
	{
		return;
	}

	UIKGameInstance* ik_game_instance = Cast<UIKGameInstance>(GetGameInstance());
	if (!ik_game_instance)
	{
		return;
	}

	UDataTableManager* data_table_manager = ik_game_instance->GetDataTableManager();
	for (EHeroType type : {EHeroType::Hero1, EHeroType::Hero2, EHeroType::Hero3, EHeroType::Hero4})
	{
		if (spawn_data_[type].is_dead_)
		{
			continue;
		}
		float max_hp = data_table_manager->GetCharacterData(HeroTypeToCharacterType(type)).status_data_.hit_point_;
		float& hp = spawn_data_[type].character_data_.status_data_.hit_point_;
		hp = FMath::Min(max_hp, hp + max_hp * heal_percentage);
	}
}

void ULevelTransitionSubsystem::HealHeroesSpawnData(float heal_amount)
{

	UIKGameInstance* ik_game_instance = Cast<UIKGameInstance>(GetGameInstance());
	if (!ik_game_instance)
	{
		return;
	}

	UDataTableManager* data_table_manager = ik_game_instance->GetDataTableManager();
	for (EHeroType type : {EHeroType::Hero1, EHeroType::Hero2, EHeroType::Hero3, EHeroType::Hero4})
	{
		if (spawn_data_[type].is_dead_)
		{
			continue;
		}
		float max_hp = data_table_manager->GetCharacterData(HeroTypeToCharacterType(type)).status_data_.hit_point_;
		float& hp = spawn_data_[type].character_data_.status_data_.hit_point_;
		hp = FMath::Min(max_hp, hp + heal_amount);
	}
}

void ULevelTransitionSubsystem::OpenMapLevel(UWorld* world)
{
	GetGameInstance()->GetSubsystem<UGlobalBuffSubsystem>()->UpdateBuffDurations();
	UGameplayStatics::OpenLevel(world, FName("MapInventoryLevel"));
}

void ULevelTransitionSubsystem::OpenNode(UWorld* world, FIntPoint map_position)
{
	UIKGameInstance* instance = Cast<UIKGameInstance>(GetGameInstance());
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

void ULevelTransitionSubsystem::ClearSpawnData()
{
	spawn_data_.Empty();
}
