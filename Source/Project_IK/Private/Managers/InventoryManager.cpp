/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.06.2025
Summary : Header file for inventory manager.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Managers/InventoryManager.h"

#include "Kismet/GameplayStatics.h"
#include "Structs/RuneData.h"
#include "WorldSettings/IKGameInstance.h"
#include "Managers/DataTableManager.h"

void UInventoryManager::InitEquipInventory()
{
	equipment_storage_.Init(FInventorySlotData(), max_inventory_size_);
	AddEquipment(EWeaponType::SniperRifle_A);
	AddEquipment(EWeaponType::Pistol_A);
	AddEquipment(EWeaponType::ShotGun_A);
	AddEquipment(EWeaponType::AssaultRifle_A);
	
	AddEquipment(EActiveSkillType::FateSpiral);
	AddEquipment(EActiveSkillType::Encourage);
	AddEquipment(EActiveSkillType::ThunderStorm);
}

void UInventoryManager::InitRuneInventory()
{
	rune_storage_.Init(FRuneSlotData(), max_inventory_size_);
	
	// AddRune(data_table_manager_cache_->GetRuneData(ERuneSetType::Chariot, 0));
	// AddRune(data_table_manager_cache_->GetRuneData(ERuneSetType::Chariot, 0));
	// AddRune(data_table_manager_cache_->GetRuneData(ERuneSetType::Chariot, 0));
	// AddRune(data_table_manager_cache_->GetRuneData(ERuneSetType::Chariot, 0));
	//
	//
	// AddRune(data_table_manager_cache_->GetRuneData(ERuneSetType::Chariot, 1));
	// AddRune(data_table_manager_cache_->GetRuneData(ERuneSetType::Chariot, 1));
	// AddRune(data_table_manager_cache_->GetRuneData(ERuneSetType::Chariot, 1));
	//
	// AddRune(data_table_manager_cache_->GetRuneData(ERuneSetType::Chariot, 2));
	// AddRune(data_table_manager_cache_->GetRuneData(ERuneSetType::Chariot, 2));
	//
	// AddRune(data_table_manager_cache_->GetRuneData(ERuneSetType::Chariot, 3));
	// AddRune(data_table_manager_cache_->GetRuneData(ERuneSetType::Chariot, 3));
	//
	// AddRune(data_table_manager_cache_->GetRuneData(ERuneSetType::Chariot, 4));
	// AddRune(data_table_manager_cache_->GetRuneData(ERuneSetType::Chariot, 4));
	//
	// AddRune(data_table_manager_cache_->GetRuneData(ERuneSetType::Chariot, 5));
}

void UInventoryManager::InitInventoryManager()
{
	TObjectPtr<UIKGameInstance> ik_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	data_table_manager_cache_ = ik_instance->GetDataTableManager();
	max_inventory_size_ = 18;
	credits_ = 200;
	perk_points_ = 12;
	tickets_ = 99;
	InitEquipInventory();
	InitRuneInventory();
}

void UInventoryManager::SetTickets(int32 tickets)
{
	tickets_ = tickets;
}

int32 UInventoryManager::GetTickets() const
{
	return tickets_;
}

int32 UInventoryManager::GetEquipmentEmptyIndex() const
{
	for (int32 i = 0; i < max_inventory_size_; ++i)
	{
		if (equipment_storage_[i].is_empty == true)
		{
			return i;
		}
	}
	return -1;
}

int32 UInventoryManager::GetRuneEmptyIndex() const
{
	for (int32 i = 0; i < max_inventory_size_; ++i)
	{
		if (rune_storage_[i].is_empty == true)
		{
			return i;
		}
	}
	return -1;
}

bool UInventoryManager::AddEquipment(EWeaponType weapon_type)
{
	int32 index = GetEquipmentEmptyIndex();
	if (index != -1)
	{
		FInventorySlotData data;
		data.weapon_type = weapon_type;
		data.gear_type = EGearType::Weapon;
		data.is_empty = false;
		equipment_storage_[index] = data;
		return true;
	}
	return false;
}

bool UInventoryManager::AddEquipment(EPassiveSkillType passive_skill_type)
{
	int32 index = GetEquipmentEmptyIndex();
	if (index != -1)
	{
		FInventorySlotData data;
		data.passive_skill_type = passive_skill_type;
		data.gear_type = EGearType::PassiveSkill;
		data.is_empty = false;
		equipment_storage_[index] = data;
		return true;
	}
	return false;
}

bool UInventoryManager::AddEquipment(EActiveSkillType active_skill_type)
{
	int32 index = GetEquipmentEmptyIndex();
	if (index != -1)
	{
		FInventorySlotData data;
		data.active_skill_type = active_skill_type;
		data.gear_type = EGearType::ActiveSkill;
		data.is_empty = false;
		equipment_storage_[index] = data;
		return true;
	}
	return false;
}

bool UInventoryManager::AddEquipment(EOopartType oopart_type)
{
	int32 index = GetEquipmentEmptyIndex();
	if (index != -1)
	{
		FInventorySlotData data;
		data.oopart_type = oopart_type;
		data.gear_type = EGearType::Oopart;
		data.is_empty = false;
		equipment_storage_[index] = data;
		return true;
	}
	return false;
}

bool UInventoryManager::AddRune(FRuneData rune_data)
{
	int32 index = GetRuneEmptyIndex();
	if (index != -1)
	{
		rune_storage_[index].rune_data = rune_data;
		rune_storage_[index].is_empty = false;
		return true;
	}
	return false;
}

bool UInventoryManager::AddRune(ERuneSetType set_type, int32 slot_idx)
{
	int32 index = GetRuneEmptyIndex();
	if (index!= -1)
	{
		rune_storage_[index].rune_data = data_table_manager_cache_->GetRuneData(set_type, slot_idx);
		rune_storage_[index].is_empty = false;
		return true;
	}
	return false;
}

void UInventoryManager::RemoveEquipItem(int index)
{
	equipment_storage_[index] = FInventorySlotData();
}

void UInventoryManager::RemoveRuneItem(int index)
{
	equipment_storage_[index] = FInventorySlotData();
}

TArray<FInventorySlotData>& UInventoryManager::GetEquipStorageData()
{
	return equipment_storage_;
}

TArray<FRuneSlotData>& UInventoryManager::GetRuneStorageData()
{
	return rune_storage_;
}

int32 UInventoryManager::GetMaxInventorySize()
{
	return max_inventory_size_;
}

void UInventoryManager::SetCredits(int32 credits)
{
	credits_ = credits;
}

void UInventoryManager::AddCredits(int32 currency)
{
	credits_ += currency;
}

int32 UInventoryManager::GetCredits() const
{
	return credits_;
}

void UInventoryManager::SetPerkPoints(int32 points)
{
	perk_points_ = points;
}

int32 UInventoryManager::GetPerkPoints() const
{
	return perk_points_;
}