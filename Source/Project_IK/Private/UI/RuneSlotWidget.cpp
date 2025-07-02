/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 3.10.2025
Summary : Source file for Rune Slot widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "UI/RuneSlotWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"
#include "UI/InventoryWidget.h"

void URuneSlotWidget::SetRuneSetSlotData(const FRuneData& rune_data)
{
	rune_data_cache_ = rune_data;
	switch (rune_data.slot_number)
	{ 
		case 0:
			slot_type_ = EInventorySlotType::Rune_0;
			break;
		case 1:
			slot_type_ = EInventorySlotType::Rune_1;
			break;
		case 2:
			slot_type_ = EInventorySlotType::Rune_2;
			break;
		case 3:
			slot_type_ = EInventorySlotType::Rune_3;
			break;
		case 4:
			slot_type_ = EInventorySlotType::Rune_4;
			break;
		case 5:
			slot_type_ = EInventorySlotType::Rune_5;
			break;
		default:
			slot_type_ = EInventorySlotType::INVALID;
	}
	SetImageTexture();
	is_empty_ = false;
}

void URuneSlotWidget::SetRuneSetSlotData(EInventorySlotType slot_type)
{
	rune_data_cache_ = FRuneData();
	slot_type_ = slot_type;
}

const FRuneData& URuneSlotWidget::GetStoredRuneData()
{
	return rune_data_cache_;
}

bool URuneSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                   UDragDropOperation* InOperation)
{
	if (Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation))
	{
		auto casted_rune_slot_widget = Cast<URuneSlotWidget>(InOperation->Payload);
		Swap(casted_rune_slot_widget->rune_data_cache_, rune_data_cache_);
		Swap(casted_rune_slot_widget->is_empty_, is_empty_);
		SetImageTexture();
		casted_rune_slot_widget->SetImageTexture();

		//장착 성공 시 세트효과 업데이트.
		inventory_widget_cache_->UpdateSetBonusEffect();
		return true;
	}
	return false;
}

void URuneSlotWidget::SetImageTexture()
{
	Super::SetImageTexture();
	image_->SetBrushFromTexture(rune_data_cache_.item_data_.thumbnail);
}
