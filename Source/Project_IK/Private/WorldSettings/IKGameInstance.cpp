/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.19.2024
Summary : Source file for game instance.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "WorldSettings/IKGameInstance.h"

#include "Abilities/ItemInventory.h"
#include "UI/IKMaps.h"
#include "Managers/ItemDataManager.h"
#include "Managers/DronePluginManager.h"
#include "Managers/TextureManager.h"
#include "Managers/DialogueEventManager.h"
#include "Managers/InventoryManager.h"
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
	InitializeItemDataManager();
	InitializeItemInventory();
	InitializeMaps();
	InitializeDronePluginManager();
	InitializeTextureManager();
	InitializeDialogueEventManager();
	InitInventoryManager();
	InitDataTableManager();
	InitSpawnData();

	item_inventory_->AddItem(item_data_manager_->GetItemData(3));
}

void UIKGameInstance::Shutdown()
{
	// Enhance data by recorded progress.
	UPerkProgressSubsystem* progress_system = GetSubsystem<UPerkProgressSubsystem>();
	const TArray<FPerkNode>& tree = GetSubsystem<UPerkTreeSubsystem>()->GetTree();

	TArray<EHeroType> types{ EHeroType::Hero1, EHeroType::Hero2, EHeroType::Hero3, EHeroType::Hero4 };
	for (EHeroType type : types)
	{
		const TSet<int32>& progress = progress_system->GetProgress(type);
		for (int32 p : progress)
		{
			character_data_manager_->DiminishCharacterData(type, tree[p].stat_, tree[p].modifier_);
		}
	}

	Super::Shutdown();
}

void UIKGameInstance::Shutdown()
{
	//TODO: 여기서 ULevelTransitionSubsystem의 저장이 필요한 data들을 disk에 write해야 함.
	Super::Shutdown();
}

void UIKGameInstance::InitSpawnData()
{
	TArray<FSpawnData> result;
	for(const auto& type : { EHeroType::Hero1, EHeroType::Hero2, EHeroType::Hero3, EHeroType::Hero4 })
	{
		FSpawnData spawn_data;
		spawn_data.character_data_ = *(data_table_manager_->GetCharacterData(type));
		result.Add(spawn_data);
	}
	GetSubsystem<ULevelTransitionSubsystem>()->UpdateSpawnData(result);
}

const UItemDataManager* UIKGameInstance::GetItemDataManager() noexcept
{
	return item_data_manager_;
}

UItemInventory* UIKGameInstance::GetItemInventory() const noexcept
{
	return item_inventory_;
}

UIKMaps* UIKGameInstance::GetMapPtr() const noexcept
{
	return maps_;
}

const UDronePluginManager* UIKGameInstance::GetDronePluginManager() noexcept
{
	return drone_plugin_manager_; 
}

UInventoryManager* UIKGameInstance::GetInventoryManager() const noexcept
{
	return inventory_manager_;
}

const UTextureManager* UIKGameInstance::GetTextureManager() const noexcept
{
	return texture_manager_;
}

const UDialogueEventManager* UIKGameInstance::GetDialogueEventManager() const noexcept
{
	return dialogue_event_manager_;
}

ULevelTransitionSubsystem* UIKGameInstance::GetLevelTransitionSubsystem() const noexcept
{
	return GetSubsystem<ULevelTransitionSubsystem>();
}

UDataTableManager* UIKGameInstance::GetDataTableManager() const noexcept
{
	return data_table_manager_;
}

void UIKGameInstance::InitializeItemDataManager()
{
	item_data_manager_ = NewObject<UItemDataManager>();
}

void UIKGameInstance::InitializeCharacterDataManager()
{
	// Enhance data by recorded progress.
	UPerkProgressSubsystem* progress_system = GetSubsystem<UPerkProgressSubsystem>();
	const TArray<FPerkNode>& tree = GetSubsystem<UPerkTreeSubsystem>()->GetTree();
	for (EHeroType type : { EHeroType::Hero1, EHeroType::Hero2, EHeroType::Hero3, EHeroType::Hero4 })
	{
		const TSet<int32>& progress = progress_system->GetProgress(type);
		for (int32 p : progress)
		{
			data_table_manager_->EnhanceCharacterData(type, tree[p].stat_, tree[p].modifier_);
		}
	}
}

void UIKGameInstance::InitializeItemInventory()
{
	item_inventory_ = NewObject<UItemInventory>(this, item_inventory_class_);
}

void UIKGameInstance::InitializeMaps()
{
	maps_ = NewObject<UIKMaps>();
	maps_->GenerateMaps(10, 5);
}

void UIKGameInstance::InitializeDronePluginManager()
{
	drone_plugin_manager_ = NewObject<UDronePluginManager>();
}

void UIKGameInstance::InitializeTextureManager()
{
	texture_manager_ = NewObject<UTextureManager>();
	texture_manager_->InitializeTextures();
}

void UIKGameInstance::InitializeDialogueEventManager()
{
	dialogue_event_manager_ = NewObject<UDialogueEventManager>();
}

void UIKGameInstance::InitInventoryManager()
{
	inventory_manager_ = NewObject<UInventoryManager>(this);
	inventory_manager_->InitInventory();
}

void UIKGameInstance::InitDataTableManager()
{
	data_table_manager_ = NewObject<UDataTableManager>(this, data_table_class_);
}