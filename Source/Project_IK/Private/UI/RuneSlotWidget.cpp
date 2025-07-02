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

void URuneSlotWidget::SetRuneSetSlotData(FRuneSetData rune_data, EInventorySlotType slot_type)
{
	rune_set_data_cache_ = rune_data;
	slot_type_ = slot_type;
}

FRuneSetData URuneSlotWidget::GetStoredRuneSetData()
{
	return rune_set_data_cache_;
}

bool URuneSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                   UDragDropOperation* InOperation)
{
	if (Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation))
	{
		auto casted_rune_slot_widget = Cast<URuneSlotWidget>(InOperation->Payload);
		Swap(casted_rune_slot_widget->rune_set_data_cache_, rune_set_data_cache_);
		SetImageTexture();
		casted_rune_slot_widget->SetImageTexture();

		//IKTODO: 룬 보드에 세트 효과를 다시 계산하라고 Notice.
		//rune_board_widget_cache_->UpdateRuneBoard();

		return true;
	}
	return false;
}

void URuneSlotWidget::SetImageTexture()
{
	Super::SetImageTexture();
	image_->SetBrushFromTexture(rune_set_data_cache_.item_data_.thumbnail);
}
