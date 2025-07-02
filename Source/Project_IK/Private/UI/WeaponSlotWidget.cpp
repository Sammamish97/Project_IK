/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.1.2025
Summary : Source file for Weapon Slot Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "UI/WeaponSlotWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"

void UWeaponSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
	slot_type_ = EInventorySlotType::Weapon;
}

void UWeaponSlotWidget::SetWeaponSlotData(FWeaponData weapon_data)
{
	weapon_data_cache_ = weapon_data;
	SetImageTexture();
}

bool UWeaponSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                     UDragDropOperation* InOperation)
{
	if (Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation))
	{
		auto casted_slot_widget = Cast<UWeaponSlotWidget>(InOperation->Payload);
		Swap(casted_slot_widget->weapon_data_cache_, weapon_data_cache_);
		Swap(casted_slot_widget->is_empty_, is_empty_);

		SetImageTexture();
		casted_slot_widget->SetImageTexture();
		return true;
	}
	return false;
}

FWeaponData UWeaponSlotWidget::GetStoredWeaponData()
{
	return weapon_data_cache_;
}


void UWeaponSlotWidget::SetImageTexture()
{
	Super::SetImageTexture();
	image_->SetBrushFromTexture(weapon_data_cache_.item_data_.thumbnail);
}