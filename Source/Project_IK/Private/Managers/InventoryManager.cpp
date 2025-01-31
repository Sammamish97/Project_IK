/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 1.10.2025
Summary : Source file for the inventory Manager.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Managers/InventoryManager.h"
#include "WorldSettings/IKGameInstance.h"
#include "Managers/DronePluginManager.h"

void UInventoryManager::InitInventory()
{
	inventory_size_ = 20;
	inventory_.Init(FDPData(), inventory_size_);
	
	credits_ = 0;

	AddDP(EDPType::FireRange);
	AddDP(EDPType::FireRateBurst);
	AddDP(EDPType::LaserBeam);

	RemoveDP(2);
}

int UInventoryManager::GetEmptyIndex() const
{
	for (int i = 0; i < inventory_size_; ++i)
	{
		if (inventory_[i].dp_type_ == EDPType::Empty)
		{
			return i;
		}
	}
	return -1;
}

bool UInventoryManager::AddDP(EDPType type)
{
	auto instance = GetWorld()->GetGameInstance();
	if (auto IK_instance = Cast<UIKGameInstance>(instance))
	{
		int index = GetEmptyIndex();
		if (index != -1)
		{
			inventory_[index] = IK_instance->GetDronePluginManager()->GetDPData(type);
			return true;
		}
	}
	return false;
}

void UInventoryManager::RemoveDP(int index)
{
	inventory_[index] = FDPData();
}

TArray<FDPData>& UInventoryManager::GetInventory()
{
	return inventory_;
}

int UInventoryManager::GetInventorySize()
{
	return inventory_size_;
}

void UInventoryManager::SetCredits(int32 credits)
{
	credits_ = credits;
}

int32 UInventoryManager::GetCredits() const
{
	return credits_;
}
