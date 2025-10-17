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
#include "UI/Map/IKMaps.h"
#include "Subsystems/LevelTransitionSubsystem.h"
#include "Managers/DataTableManager.h"

#include "Subsystems/GlobalBuffSubsystem.h"
#include "Kismet/GameplayStatics.h"
#include "SaveGame/SaveRunProgress.h"
#include "Managers/InventoryManager.h"

#include "Subsystems/AudioManagerSubsystem.h"

#include "Subsystems/RandomNumberGeneratorSubsystem.h"

void AIKMapGameMode::BeginPlay()
{
	Super::BeginPlay();

	SaveGameData();

	HealHeroesAfterCombat();

	UAudioManagerSubsystem::Get(this)->Play2D(EAudioType::MapAmbient);
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

void AIKMapGameMode::SaveGameData()
{
	USaveRunProgress* save_game_instance = Cast<USaveRunProgress>(UGameplayStatics::CreateSaveGameObject(USaveRunProgress::StaticClass()));

	UIKGameInstance* game_instance = Cast<UIKGameInstance>(GetGameInstance());

	if (save_game_instance && game_instance)
	{
		UIKMaps* map = game_instance->GetMapPtr();
		save_game_instance->rand_seed_for_map_ = map->GetRandSeedForMap();
		save_game_instance->map_height_ = map->GetHeight();
		save_game_instance->map_width_ = map->GetWidth();
		save_game_instance->player_visited_path_ = map->GetPlayerVisitedPath();

		save_game_instance->spawn_data_ = game_instance->GetSubsystem<ULevelTransitionSubsystem>()->GetSpawnData();
		save_game_instance->credits_ = game_instance->GetInventoryManager()->GetCredits();

		UGlobalBuffSubsystem* subsystem = game_instance->GetSubsystem<UGlobalBuffSubsystem>();
		TArray<FGlobalBuffData> buffs = subsystem->GetBuffs();
		for (const FGlobalBuffData& global_buff : buffs)
		{
			save_game_instance->applied_global_buffs_.Add(global_buff.buff_type_, global_buff.duration_);
		}

		save_game_instance->rand_seed_ = URandomNumberGeneratorSubsystem::GetRNG(GetWorld()).GetCurrentSeed();

		UGameplayStatics::SaveGameToSlot(save_game_instance, save_game_instance->GetSaveSlotName(), 0);
	}
}
