/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 3.11.2025
Summary : Header file for Equipment Storage widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/EquipStorageWidget.h"

#include "Components/ScrollBox.h"
#include "Components/WrapBox.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/InventoryManager.h"
#include "UI/InventorySlot.h"
#include "WorldSettings/IKGameInstance.h"

void UEquipStorageWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UEquipStorageWidget::LoadEquipStorage()
{
	TObjectPtr<UIKGameInstance> ik_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	TObjectPtr<UInventoryManager> inventory_manager_cache = ik_instance->GetInventoryManager();

	scroll_box_->ClearChildren();
	wrap_box_->ClearChildren();
	equip_inventory_slots_.Reset();
	equip_inventory_slots_.Init(nullptr, inventory_manager_cache->GetMaxInventorySize());
	auto inventory_data = inventory_manager_cache->GetEquipStorageData();

	int32 data_count = 0;
	for (auto elem : inventory_data)
	{
		equip_inventory_slots_[data_count] = Cast<UInventorySlot>(CreateWidget(GetWorld(), slot_BP_class_));
		equip_inventory_slots_[data_count]->slot_data_ = inventory_data[data_count];
		equip_inventory_slots_[data_count]->slot_type_ = EInventorySlotType::InventorySlot;
		equip_inventory_slots_[data_count]->grid_idx_ = data_count;
		equip_inventory_slots_[data_count]->SetImageTexture();
		wrap_box_->AddChild(equip_inventory_slots_[data_count]);
		data_count+=1;
	}
	
	for(int32 i = data_count; i < inventory_manager_cache->GetMaxInventorySize(); i++)
	{
		equip_inventory_slots_[i] = Cast<UInventorySlot>(CreateWidget(GetWorld(), slot_BP_class_));
		equip_inventory_slots_[i]->slot_data_ = FInventorySlotData();
		equip_inventory_slots_[i]->slot_type_ = EInventorySlotType::InventorySlot;
		equip_inventory_slots_[i]->grid_idx_ = i;
		equip_inventory_slots_[i]->SetImageTexture();
		wrap_box_->AddChild(equip_inventory_slots_[i]);
	}
	scroll_box_->AddChild(wrap_box_);
}

void UEquipStorageWidget::UpdateEquipStorage()
{
	TObjectPtr<UIKGameInstance> ik_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	TObjectPtr<UInventoryManager> inventory_manager_cache = ik_instance->GetInventoryManager();

	auto& equip_storage_data = inventory_manager_cache->GetEquipStorageData();
	equip_storage_data.Empty();
	
	for (auto& elem : equip_inventory_slots_)
	{
		if (elem != nullptr && elem->slot_data_.is_empty == false)
		{
			equip_storage_data.Add(elem->slot_data_);
		}
	}
}