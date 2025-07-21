/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 02.27.2025
Summary : Source file for Map level game mode class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "WorldSettings/Map/IKMapGameMode.h"

#include "Subsystems/PerkModifierSubsystem.h"
#include "WorldSettings/IKGameInstance.h"
#include "UI/IKMaps.h"
#include "Subsystems/LevelTransitionSubsystem.h"
#include "Managers/DataTableManager.h"


void AIKMapGameMode::BeginPlay()
{
	HealHeroesAfterCombat();
}

void AIKMapGameMode::HealHeroesAfterCombat()
{
	UGameInstance* game_instance = GetGameInstance();
	UIKGameInstance* ik_game_instance = Cast<UIKGameInstance>(game_instance);

	float heal_percentage = game_instance->GetSubsystem<UPerkModifierSubsystem>()->GetCombatEndHealPercentage();

	if (heal_percentage <= 0.f)
	{
		return;
	}

	UIKMaps* map = ik_game_instance->GetMapPtr();
	TArray<FIntPoint> path = map->GetPlayerVisitedPath();
	if (path.IsEmpty())
	{
		return;
	}
	const FMapNode& node = map->GetNode(path.Last());
	if (node.type != NodeType::Enemy)
	{
		return;
	}

	ULevelTransitionSubsystem* level_transition_subsystem = game_instance->GetSubsystem<ULevelTransitionSubsystem>();
	UDataTableManager* data_table_manager = ik_game_instance->GetDataTableManager();
	TMap<EHeroType, FSpawnData> spawn_map = level_transition_subsystem->GetSpawnData();
	for (EHeroType type : {EHeroType::Hero1, EHeroType::Hero2, EHeroType::Hero3, EHeroType::Hero4})
	{
		if (spawn_map[type].is_dead_)
		{
			continue;
		}
		float max_hp = data_table_manager->GetCharacterData(HeroTypeToCharacterType(type)).status_data_.hit_point_;
		float& hp = spawn_map[type].character_data_.status_data_.hit_point_;
		hp = FMath::Max(max_hp, hp + max_hp * heal_percentage);
	}
}
