/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.19.2024
Summary : Source file for game instance.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "WorldSettings/IKGameInstance.h"

#include "UI/IKMaps.h"
#include "Managers/InventoryManager.h"
#include "Managers/SetBonusManager.h"
#include "Managers/EventManager.h"
#include "Managers/DataTableManager.h"

#include "Structs/SpawnData.h"
#include "Abilities/PerkEffects/PerkEffectBase.h"

#include "Subsystems/PerkProgressSubsystem.h"
#include "Subsystems/LevelTransitionSubsystem.h"
#include "Subsystems/GlobalBuffSubsystem.h"

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
	InitSpawnData();
	InitSetBonusManager();
	InitEventManager();

	InitializePerkEffectsAlreadyUnlocked();
}

void UIKGameInstance::Shutdown()
{
	// Enhance data by recorded progress.
	UPerkProgressSubsystem* progress_system = GetSubsystem<UPerkProgressSubsystem>();
	const TArray<FPerkNode>& tree = GetTree();

	const TSet<int32>& progress = progress_system->GetProgress();
	for (int32 p : progress)
	{
		UPerkEffectBase* perk_effect = NewObject<UPerkEffectBase>(this, tree[p].effect_class_);
		if (perk_effect)
		{
			perk_effect->RemoveEffect();
		}
	}

	//TODO: 여기서 ULevelTransitionSubsystem의 저장이 필요한 data들을 disk에 write해야 함.
	Super::Shutdown();
}

void UIKGameInstance::ClearRunData()
{

	UGlobalBuffSubsystem* global_buff_subsystem = GetSubsystem<UGlobalBuffSubsystem>();
	global_buff_subsystem->ClearBuffs();

	int32 height = maps_->GetHeight();
	int32 width = maps_->GetWidth();
	maps_->GenerateMaps(height, width);

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
		if (i != 0)
		{
			spawn_data.is_dead_ = true;
		}
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

void UIKGameInstance::InitEventManager()
{
	event_manager_ = NewObject<UEventManager>(this, event_manager_class_);
	event_manager_->InitEventManager(this, inventory_manager_);
}

void UIKGameInstance::InitializePerkEffectsAlreadyUnlocked()
{
	// Enhance data by recorded progress.
	UPerkProgressSubsystem* progress_system = GetSubsystem<UPerkProgressSubsystem>();
	const TArray<FPerkNode>& tree = GetTree();
	const TSet<int32>& progress = progress_system->GetProgress();
	for (int32 p : progress)
	{
		UPerkEffectBase* perk_effect = NewObject<UPerkEffectBase>(this, tree[p].effect_class_);
		if (perk_effect)
		{
			perk_effect->ApplyEffect();
		}
	}
}

void UIKGameInstance::InitializeMaps()
{
	maps_ = NewObject<UIKMaps>();
	maps_->GenerateMaps(10, 5);
}

void UIKGameInstance::InitInventoryManager()
{
	inventory_manager_ = NewObject<UInventoryManager>(this, inventory_manager_class_);

	// DEBUG PURPOSE.
	inventory_manager_->SetPerkPoints(999);
	inventory_manager_->SetCredits(999);
}

void UIKGameInstance::InitDataTableManager()
{
	data_table_manager_ = NewObject<UDataTableManager>(this, data_table_class_);
}

void UIKGameInstance::InitSetBonusManager()
{
	set_bonus_manager_ = NewObject<USetBonusManager>(this, set_bonus_class_);
}