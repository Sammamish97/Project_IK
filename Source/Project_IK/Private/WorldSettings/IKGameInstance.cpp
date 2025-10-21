/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.19.2024
Summary : Source file for game instance.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "WorldSettings/IKGameInstance.h"

#include "UI/Map/IKMaps.h"
#include "Managers/InventoryManager.h"
#include "Managers/SetBonusManager.h"
#include "Managers/EventManager.h"
#include "Managers/DataTableManager.h"

#include "Structs/SpawnData.h"
#include "Abilities/PerkEffects/PerkEffectBase.h"
#include "Managers/PauseManager.h"
#include "Managers/TextManager.h"

#include "Subsystems/PerkProgressSubsystem.h"
#include "Subsystems/LevelTransitionSubsystem.h"
#include "Subsystems/GlobalBuffSubsystem.h"

// Header files for saved data
#include "SaveGame/SavePerkProgress.h"
#include "SaveGame/SaveRunProgress.h"
#include "SaveGame/SaveSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Subsystems/AudioManagerSubsystem.h"
#include "Subsystems/RandomNumberGeneratorSubsystem.h"

UIKGameInstance::UIKGameInstance()
	:Super::UGameInstance()
{
}

void UIKGameInstance::Init()
{
	Super::Init();
	InitializeMaps();
	InitDataTableManager();
	InitInventoryManager();
	InitSetBonusManager();
	InitTextManager();
	InitEventManager();

	LoadSaveData();

	// Function call matters. PerkEffects -> InitSpawnData
	InitializePerkEffectsAlreadyUnlocked();
}

void UIKGameInstance::Shutdown()
{
	UPerkProgressSubsystem* subsystem = GetSubsystem<UPerkProgressSubsystem>();
	subsystem->RemoveAllPerkEffects();
	
	Super::Shutdown();
}

void UIKGameInstance::ClearRunData()
{

	UGlobalBuffSubsystem* global_buff_subsystem = GetSubsystem<UGlobalBuffSubsystem>();
	global_buff_subsystem->ClearBuffs();

	USaveRunProgress::StaticClass()->GetDefaultObject<USaveRunProgress>()->DeleteSaveFile();

	InitSpawnData();
}

void UIKGameInstance::InitSpawnData()
{
	TMap<EHeroType, FSpawnData> spawn_data_map;
	TArray char_type_array = { ECharacterType::Hero1, ECharacterType::Hero2, ECharacterType::Hero3, ECharacterType::Hero4 };
	TArray hero_type_array = { EHeroType::Hero1, EHeroType::Hero2, EHeroType::Hero3, EHeroType::Hero4 };
	for (int32 i = 0; i < 4; ++i)
	{
		FSpawnData spawn_data;
		spawn_data.character_data_ = data_table_manager_->GetCharacterData(char_type_array[i]);
		spawn_data_map.Add({ hero_type_array[i], spawn_data });
	}
	GetSubsystem<ULevelTransitionSubsystem>()->UpdateSpawnData(spawn_data_map);
}

UIKMaps* UIKGameInstance::GetMapPtr() const noexcept
{
	return maps_;
}

UInventoryManager* UIKGameInstance::GetInventoryManager() const noexcept
{
	return inventory_manager_;
}

ULevelTransitionSubsystem* UIKGameInstance::GetLevelTransitionSubsystem() const noexcept
{
	return GetSubsystem<ULevelTransitionSubsystem>();
}

UDataTableManager* UIKGameInstance::GetDataTableManager() const noexcept
{
	return data_table_manager_;
}

void UIKGameInstance::EnhanceHeroesStatData(ECharacterStatType stat_type, float increase_amount)
{
	data_table_manager_->EnhanceHeroesStatData(stat_type, increase_amount);
}

void UIKGameInstance::DiminishHeroesStatData(ECharacterStatType stat_type, float decrease_amount)
{
	data_table_manager_->DiminishHeroesStatData(stat_type, decrease_amount);
}

const TArray<FPerkNode>& UIKGameInstance::GetTree() const
{
	return data_table_manager_->GetTree();
}

USetBonusManager* UIKGameInstance::GetSetBonusManager() const noexcept
{
	return set_bonus_manager_;
}

UEventManager* UIKGameInstance::GetEventManager() const noexcept
{
	return event_manager_;
}

UTextManager* UIKGameInstance::GetTextManager() const noexcept
{
	return text_manager_;
}

void UIKGameInstance::InitEventManager()
{
	event_manager_ = NewObject<UEventManager>(this, event_manager_class_);
	event_manager_->InitEventManager(this, inventory_manager_, text_manager_);
}

void UIKGameInstance::InitializePerkEffectsAlreadyUnlocked()
{
	//Enhance data by recorded progress.
	 UPerkProgressSubsystem* progress_system = GetSubsystem<UPerkProgressSubsystem>();
	 progress_system->ApplyPerkEffectsInMap();
}

void UIKGameInstance::InitializeMaps()
{
	maps_ = NewObject<UIKMaps>(this);
}

void UIKGameInstance::InitInventoryManager()
{
	inventory_manager_ = NewObject<UInventoryManager>(this, inventory_manager_class_);

	// DEBUG PURPOSE.
	inventory_manager_->SetCredits(0);
}

void UIKGameInstance::InitDataTableManager()
{
	data_table_manager_ = NewObject<UDataTableManager>(this, data_table_class_);
}

void UIKGameInstance::InitSetBonusManager()
{
	set_bonus_manager_ = NewObject<USetBonusManager>(this, set_bonus_class_);
}

void UIKGameInstance::InitTextManager()
{
	text_manager_ = NewObject<UTextManager>(this, text_manager_class_);
}

void UIKGameInstance::LoadSaveData()
{
	USaveSettings* settings = Cast<USaveSettings>(UGameplayStatics::LoadGameFromSlot(USaveSettings::StaticClass()->GetDefaultObject<USaveSettings>()->GetSaveSlotName(), 0));
	if (settings)
	{
		UAudioManagerSubsystem* audio_subsystem = UAudioManagerSubsystem::Get(this);
		if (audio_subsystem)
		{
			audio_subsystem->SetMasterVolume(settings->master_volume_);
			audio_subsystem->SetBGMVolume(settings->music_volume_);
			audio_subsystem->SetSFXVolume(settings->sfx_volume_);
		}
	}
	else
	{
		// No save data
	}


	USavePerkProgress* saved_perk_progress = Cast<USavePerkProgress>(UGameplayStatics::LoadGameFromSlot(USavePerkProgress::StaticClass()->GetDefaultObject<USavePerkProgress>()->GetSaveSlotName(), 0));
	if (saved_perk_progress)
	{
		UPerkProgressSubsystem* perk_progress_subsystem = GetSubsystem<UPerkProgressSubsystem>();
		if (perk_progress_subsystem)
		{
			for (const auto& [perk_name, perk_node_detail] : saved_perk_progress->perk_node_map_)
			{
				perk_progress_subsystem->SavePerkDetails(perk_name, perk_node_detail);
			}
			perk_progress_subsystem->SavePerkPoint(saved_perk_progress->perk_points_);
		}
	}
	else
	{
		// No save data
	}

	LoadRunSaveData();
}

// Move this function to USaveRunProgress
void UIKGameInstance::LoadRunSaveData()
{
	USaveRunProgress* saved_run = Cast<USaveRunProgress>(UGameplayStatics::LoadGameFromSlot(USaveRunProgress::StaticClass()->GetDefaultObject<USaveRunProgress>()->GetSaveSlotName(), 0));
	if (saved_run)
	{
		maps_->RecoverMaps(saved_run->rand_seed_for_map_, saved_run->map_height_, saved_run->map_width_, saved_run->player_visited_path_);

		ULevelTransitionSubsystem* level_transition_subsystem = GetSubsystem<ULevelTransitionSubsystem>();
		if (level_transition_subsystem)
		{
			level_transition_subsystem->UpdateSpawnData(saved_run->spawn_data_);
		}
		inventory_manager_->SetCredits(saved_run->credits_);

		UGlobalBuffSubsystem* global_buff_subsystem = GetSubsystem<UGlobalBuffSubsystem>();
		if (global_buff_subsystem)
		{
			global_buff_subsystem->RecoverBuffs(saved_run->applied_global_buffs_);
		}

		URandomNumberGeneratorSubsystem::GetRNG(GetWorld()).Initialize(saved_run->rand_seed_);
	}
	else
	{
		// No save data

		// Initialize map data to prevent game crash during developments.
		maps_->GenerateMaps(10, 5);
		InitSpawnData();
		inventory_manager_->SetCredits(0);
	}
}

bool UIKGameInstance::IsFirstBattle()
{
	USaveRunProgress* saved_run = Cast<USaveRunProgress>(UGameplayStatics::LoadGameFromSlot(USaveRunProgress::StaticClass()->GetDefaultObject<USaveRunProgress>()->GetSaveSlotName(), 0));
	if (saved_run)
	{
		return saved_run->is_first_battle_;
	}
	return false;
}

bool UIKGameInstance::IsFirstInventory()
{
	USaveRunProgress* saved_run = Cast<USaveRunProgress>(UGameplayStatics::LoadGameFromSlot(USaveRunProgress::StaticClass()->GetDefaultObject<USaveRunProgress>()->GetSaveSlotName(), 0));
	if (saved_run)
	{
		return saved_run->is_first_inventory_;
	}
	return false;
}

void UIKGameInstance::SetIsFirstBattleFalse()
{
	USaveRunProgress* save_game_instance = Cast<USaveRunProgress>(UGameplayStatics::LoadGameFromSlot(USaveRunProgress::StaticClass()->GetDefaultObject<USaveRunProgress>()->GetSaveSlotName(), 0));
	if (save_game_instance == nullptr)
	{
		save_game_instance = Cast<USaveRunProgress>(UGameplayStatics::CreateSaveGameObject(USaveRunProgress::StaticClass()));
	}
	save_game_instance->is_first_battle_ = false;
	UGameplayStatics::SaveGameToSlot(save_game_instance, save_game_instance->GetSaveSlotName(), 0);
}

void UIKGameInstance::SetIsFirstInventoryFalse()
{
	USaveRunProgress* save_game_instance = Cast<USaveRunProgress>(UGameplayStatics::LoadGameFromSlot(USaveRunProgress::StaticClass()->GetDefaultObject<USaveRunProgress>()->GetSaveSlotName(), 0));
	if (save_game_instance == nullptr)
	{
		save_game_instance = Cast<USaveRunProgress>(UGameplayStatics::CreateSaveGameObject(USaveRunProgress::StaticClass()));
	}
	save_game_instance->is_first_inventory_ = false;
	UGameplayStatics::SaveGameToSlot(save_game_instance, save_game_instance->GetSaveSlotName(), 0);
}
