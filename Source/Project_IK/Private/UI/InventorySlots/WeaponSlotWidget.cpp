/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.1.2025
Summary : Source file for Weapon Slot Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "UI/InventorySlots/WeaponSlotWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"
#include "UI/InventoryWidget.h"

void UWeaponSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
	slot_type_ = EInventorySlotType::Weapon;
}

void UWeaponSlotWidget::SetWeaponSlotData(const FWeaponData& weapon_data)
{
	is_empty_ = false;
	weapon_data_cache_ = weapon_data;
	item_data_cache_ = weapon_data_cache_.item_data_;
	SetImageTexture();
}

FReply UWeaponSlotWidget::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	inventory_widget_cache_->SetHighlightVisibility(EGearType::Weapon, ESlateVisibility::Visible);
	return Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);}

bool UWeaponSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                     UDragDropOperation* InOperation)
{
	if (Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation))
	{
		auto casted_slot = Cast<UWeaponSlotWidget>(InOperation->Payload);
		if (casted_slot->is_board_slot_)
		{
			Swap(casted_slot->weapon_data_cache_, weapon_data_cache_);
			Swap(casted_slot->is_empty_, is_empty_);
			SetImageTexture();
			casted_slot->SetImageTexture();
		}
		else
		{
			if (is_empty_ == false)
			{
				inventory_widget_cache_->AddToRewardContainer(this);
			}
			SetWeaponSlotData(casted_slot->weapon_data_cache_);
			inventory_widget_cache_->RemoveFromRewardContainer(casted_slot);
		}
		return true;
	}
	return false;
}

void UWeaponSlotWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (is_empty_ == false)
	{
		FText detail;
		inventory_widget_cache_->CreateWeaponPopupWidget(item_data_cache_.display_data_->thumbnail,
			text_manager_cache_->GetActiveSkillNameText(item_data_cache_.display_data_->text_key_),
			detail,
			weapon_data_cache_.status_data_);
	}
}

FWeaponData UWeaponSlotWidget::GetStoredWeaponData()
{
	return weapon_data_cache_;
}

void UWeaponSlotWidget::SetImageTexture()
{
	Super::SetImageTexture();
	image_->SetBrushFromTexture(weapon_data_cache_.item_data_.display_data_->thumbnail);
}

void UWeaponSlotWidget::ClearData()
{
	Super::ClearData();
	weapon_data_cache_ = FWeaponData();
}
