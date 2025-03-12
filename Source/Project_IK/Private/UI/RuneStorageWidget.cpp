/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 3.11.2025
Summary : Source file for Rune Storage widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/RuneStorageWidget.h"

#include "Components/ScrollBox.h"
#include "Components/WrapBox.h"
#include "Kismet/GameplayStatics.h"

#include "Managers/InventoryManager.h"
#include "UI/RuneSlotWidget.h"
#include "WorldSettings/IKGameInstance.h"

class UIKGameInstance;

void URuneStorageWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void URuneStorageWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void URuneStorageWidget::LoadRuneStorage()
{
	TObjectPtr<UIKGameInstance> ik_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	TObjectPtr<UInventoryManager> inventory_manager_cache = ik_instance->GetInventoryManager();

	scroll_box_->ClearChildren();
	wrap_box_->ClearChildren();
	rune_inventory_slots_.Reset();
	rune_inventory_slots_.Init(nullptr, inventory_manager_cache->GetMaxInventorySize());
	auto inventory_data = inventory_manager_cache->GetRuneInventory();
	for(int i = 0; i < inventory_data.Num(); i++)
	{
		rune_inventory_slots_[i] = CreateWidget<URuneSlotWidget>(GetWorld(), slot_BP_class_);
		rune_inventory_slots_[i]->SetRuneData(inventory_data[i]);
		rune_inventory_slots_[i]->SetImageTexture();
		wrap_box_->AddChild(rune_inventory_slots_[i]);
	}
	scroll_box_->AddChild(wrap_box_);
}
