/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.06.2025
Summary : Header file for inventory manager.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Managers/HeroInventoryManager.h"

void UHeroInventoryManager::InitInventory()
{
	inventory_size_ = 20;
	inventory_.Init(FInventorySlotData(), inventory_size_);

	AddItem(EGearType::Armor, EArmorType::TestSkillArmor);
	AddItem(EGearType::Trinket, ETrinketType::TestAttack);
	AddItem(EGearType::Weapon, EWeaponType::Pistol);
	AddItem(EGearType::Weapon, EWeaponType::AssaultRifle);
	AddItem(EGearType::PassiveSkill, EPassiveSkillType::FixedDmgReduce);
	AddItem(EGearType::PassiveSkill, EPassiveSkillType::RandDmgIncrease);

	credits_ = 0;

	perk_points_ = 12;
}

int32 UHeroInventoryManager::GetEmptyIndex() const
{
	for (int32 i = 0; i < inventory_size_; ++i)
	{
		if (inventory_[i].is_empty == true)
		{
			return i;
		}
	}
	return -1;
}

bool UHeroInventoryManager::AddItem(EGearType gear_type, EArmorType armor_type)
{
	int32 index = GetEmptyIndex();
	if (index != -1)
	{
		FInventorySlotData data;
		data.armor_type = armor_type;
		data.gear_type = gear_type;
		data.is_empty = false;
		inventory_[index] = data;
		return true;
	}
	return false;
}

bool UHeroInventoryManager::AddItem(EGearType gear_type, ETrinketType trinket_type)
{
	int32 index = GetEmptyIndex();
	if (index != -1)
	{
		FInventorySlotData data;
		data.trinket_type = trinket_type;
		data.gear_type = gear_type;
		data.is_empty = false;
		inventory_[index] = data;
		return true;
	}
	return false;
}

bool UHeroInventoryManager::AddItem(EGearType type, EWeaponType weapon_type)
{
	int32 index = GetEmptyIndex();
	if (index != -1)
	{
		FInventorySlotData data;
		data.weapon_type = weapon_type;
		data.gear_type = type;
		data.is_empty = false;
		inventory_[index] = data;
		return true;
	}
	return false;
}

bool UHeroInventoryManager::AddItem(EGearType type, EPassiveSkillType passive_skill_type)
{
	int32 index = GetEmptyIndex();
	if (index != -1)
	{
		FInventorySlotData data;
		data.passive_skill_type = passive_skill_type;
		data.gear_type = type;
		data.is_empty = false;
		inventory_[index] = data;
		return true;
	}
	return false;
}

void UHeroInventoryManager::RemoveItem(int index)
{
	inventory_[index] = FInventorySlotData();
}

TArray<FInventorySlotData>& UHeroInventoryManager::GetInventory()
{
	return inventory_;
}

int32 UHeroInventoryManager::GetInventorySize()
{
	return inventory_size_;
}

void UHeroInventoryManager::SetCredits(int32 credits)
{
	credits_ = credits;
}

int32 UHeroInventoryManager::GetCredits() const
{
	return credits_;
}

void UHeroInventoryManager::SetPerkPoints(int32 points)
{
	perk_points_ = points;
}

int32 UHeroInventoryManager::GetPerkPoints() const
{
	return perk_points_;
}
