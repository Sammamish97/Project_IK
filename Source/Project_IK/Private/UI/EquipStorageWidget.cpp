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
	auto inventory_data = inventory_manager_cache->GetEquipInventory();
	for(int i = 0; i < inventory_data.Num(); i++)
	{
		equip_inventory_slots_[i] = Cast<UInventorySlot>(CreateWidget(GetWorld(), slot_BP_class_));
		equip_inventory_slots_[i]->slot_data_ = inventory_data[i];
		equip_inventory_slots_[i]->slot_type_ = EInventorySlotType::Inventory;
		equip_inventory_slots_[i]->grid_idx_ = i;
		equip_inventory_slots_[i]->SetImageTexture();
		wrap_box_->AddChild(equip_inventory_slots_[i]);
	}
	scroll_box_->AddChild(wrap_box_);
}
