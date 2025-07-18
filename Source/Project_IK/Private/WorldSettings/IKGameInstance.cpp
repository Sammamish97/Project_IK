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

#include "Subsystems/PerkProgressSubsystem.h"
#include "Subsystems/PerkTreeSubsystem.h"
#include "Subsystems/LevelTransitionSubsystem.h"

UIKGameInstance::UIKGameInstance()
	:Super::UGameInstance()
{
}

void UIKGameInstance::Init()
{
	Super::Init();

	InitializeCharacterDataManager();
	InitializeMaps();
	InitDataTableManager();
	InitInventoryManager();
	InitSpawnData();
	InitSetBonusManager();
	InitEventManager();
}

void UIKGameInstance::Shutdown()
{
	// Enhance data by recorded progress.
	UPerkProgressSubsystem* progress_system = GetSubsystem<UPerkProgressSubsystem>();
	const TArray<FPerkNode>& tree = GetSubsystem<UPerkTreeSubsystem>()->GetTree();

	for (ECharacterType type : { ECharacterType::Hero1, ECharacterType::Hero2, ECharacterType::Hero3, ECharacterType::Hero4 })
	{
		const TSet<int32>& progress = progress_system->GetProgress(type);
		for (int32 p : progress)
		{
			data_table_manager_->DiminishCharacterData(type, tree[p].stat_, tree[p].modifier_);
		}
	}

	//TODO: 여기서 ULevelTransitionSubsystem의 저장이 필요한 data들을 disk에 write해야 함.
	Super::Shutdown();
}

void UIKGameInstance::InitSpawnData()
{
	TMap<EHeroType, FSpawnData> spawn_data_map;
	TArray char_type_array = { ECharacterType::Hero1, ECharacterType::Hero2, ECharacterType::Hero3, ECharacterType::Hero4 };
	TArray hero_type_array = {EHeroType::Hero1, EHeroType::Hero2, EHeroType::Hero3, EHeroType::Hero4};
	for(int32 i = 0; i < 4; ++i)
	{
		FSpawnData spawn_data;
		spawn_data.character_data_ = data_table_manager_->GetCharacterData(char_type_array[i]);
		spawn_data_map.Add({hero_type_array[i], spawn_data});
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

void UIKGameInstance::InitializeCharacterDataManager()
{
	// Enhance data by recorded progress.
	UPerkProgressSubsystem* progress_system = GetSubsystem<UPerkProgressSubsystem>();
	const TArray<FPerkNode>& tree = GetSubsystem<UPerkTreeSubsystem>()->GetTree();
	for (ECharacterType type : { ECharacterType::Hero1, ECharacterType::Hero2, ECharacterType::Hero3, ECharacterType::Hero4 })
	{
		const TSet<int32>& progress = progress_system->GetProgress(type);
		for (int32 p : progress)
		{
			data_table_manager_->EnhanceCharacterData(type, tree[p].stat_, tree[p].modifier_);
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
}

void UIKGameInstance::InitDataTableManager()
{
	data_table_manager_ = NewObject<UDataTableManager>(this, data_table_class_);
}

void UIKGameInstance::InitSetBonusManager()
{
	set_bonus_manager_ = NewObject<USetBonusManager>(this, set_bonus_class_);
}