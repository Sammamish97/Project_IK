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
#include "Managers/CharacterDataManager.h"
#include "Managers/LevelTransitionManager.h"
#include "Managers/DronePluginManager.h"
#include "Managers/TextureManager.h"
#include "Managers/DialogueEventManager.h"
#include "Managers/HeroInventoryManager.h"
#include "Managers/EquipManager.h"

#include "Subsystems/PerkProgressSubsystem.h"
#include "Subsystems/PerkTreeSubsystem.h"

#include "Characters/HeroBase.h"
#include "Characters/EnemyBase.h"

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
	InitializeLevelTransitionManager();
	InitializeDronePluginManager();
	InitializeTextureManager();
	InitializeDialogueEventManager();
	InitInventoryManager();
	InitEquipManager();

	item_inventory_->AddItem(item_data_manager_->GetItemDataRandomly());
}

const UItemDataManager* UIKGameInstance::GetItemDataManager() noexcept
{
	return item_data_manager_;
}

UCharacterDataManager* UIKGameInstance::GetCharacterDataManager() noexcept
{
	return character_data_manager_;
}

UItemInventory* UIKGameInstance::GetItemInventory() const noexcept
{
	return item_inventory_;
}

UIKMaps* UIKGameInstance::GetMapPtr() const noexcept
{
	return maps_;
}

ULevelTransitionManager* UIKGameInstance::GetLevelTransitionManager() noexcept
{
	return level_transition_manager_;
}

const UDronePluginManager* UIKGameInstance::GetDronePluginManager() noexcept
{
	return drone_plugin_manager_; 
}

UHeroInventoryManager* UIKGameInstance::GetInventoryManager() const noexcept
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

UEquipManager* UIKGameInstance::GetEquipManager() const noexcept
{
	return equip_manager_;
}

void UIKGameInstance::InitializeItemDataManager()
{
	item_data_manager_ = NewObject<UItemDataManager>();
}

void UIKGameInstance::InitializeCharacterDataManager()
{
	character_data_manager_ = NewObject<UCharacterDataManager>();
	
	// Enhance data by recorded progress.
	UPerkProgressSubsystem* progress_system = GetSubsystem<UPerkProgressSubsystem>();
	const TArray<FPerkNode>& tree = GetSubsystem<UPerkTreeSubsystem>()->GetTree();

	TArray<EHeroType> types{ EHeroType::Hero1, EHeroType::Hero2, EHeroType::Hero3, EHeroType::Hero4 };
	for (EHeroType type : types)
	{
		const TSet<int32>& progress = progress_system->GetProgress(type);
		for (int32 p : progress)
		{
			character_data_manager_->EnhanceCharacterData(type, tree[p].stat_, tree[p].modifier_);
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

void UIKGameInstance::InitializeLevelTransitionManager()
{
	level_transition_manager_ = NewObject<ULevelTransitionManager>();
	level_transition_manager_->SetActorBlueprints(hero_blueprint_, enemy_blueprint_);
	level_transition_manager_->SetInstanceCache(this);
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
	inventory_manager_ = NewObject<UHeroInventoryManager>(this);
	inventory_manager_->InitInventory();
}

void UIKGameInstance::InitEquipManager()
{
	equip_manager_ = NewObject<UEquipManager>(this);
}
