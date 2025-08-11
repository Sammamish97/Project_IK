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
	level_transition_subsystem->HealHeroesSpawnDataPercentage(heal_percentage);
}
