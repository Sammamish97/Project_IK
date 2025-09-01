/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 3.10.2025
Summary : Source file for Rune Slot widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "UI/InventorySlots/RuneSlotWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Border.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "DataAssets/DisplayDataAsset.h"
#include "UI/Inventory/InventoryWidget.h"

void URuneSlotWidget::SetRuneSetSlotData(const FRuneData& rune_data)
{
	rune_data_cache_ = rune_data;
	item_data_cache_ = rune_data_cache_.item_data_;
	rune_idx_text_->SetText(FText::AsNumber(rune_data.slot_number));
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
	SetRuneRelatedWidgetsVisibility(ESlateVisibility::HitTestInvisible);
	is_empty_ = false;
}

void URuneSlotWidget::SetRuneSetSlotData(EInventorySlotType slot_type)
{
	rune_data_cache_ = FRuneData();
	slot_type_ = slot_type;
	item_data_cache_ = FItemData();
	SetRuneRelatedWidgetsVisibility(ESlateVisibility::Hidden);
}

void URuneSlotWidget::SetRuneRelatedWidgetsVisibility(ESlateVisibility visibility)
{
	rune_idx_text_->SetVisibility(visibility);
	//rune_idx_background_->SetVisibility(visibility);
	rune_idx_border_->SetVisibility(visibility);
}

const FRuneData& URuneSlotWidget::GetStoredRuneData()
{
	return rune_data_cache_;
}

FReply URuneSlotWidget::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	inventory_widget_cache_->SetHighlightVisibility(rune_data_cache_.slot_number, ESlateVisibility::Visible);
	return Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);
}

bool URuneSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                   UDragDropOperation* InOperation)
{
	if (Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation))
	{
		auto casted_rune_slot_widget = Cast<URuneSlotWidget>(InOperation->Payload);
		
		if (casted_rune_slot_widget->is_board_slot_ == false)
		{
			if (is_empty_ == false)
			{
				inventory_widget_cache_->AddToRewardContainer(this);
			}
			SetRuneSetSlotData(casted_rune_slot_widget->GetStoredRuneData());
			inventory_widget_cache_->RemoveFromRewardContainer(casted_rune_slot_widget);
		}
		inventory_widget_cache_->UpdateSetBonusEffect();
		return true;
	}
	return false;
}

void URuneSlotWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (is_empty_ == false)
	{
		inventory_widget_cache_->CreateRunePopupWidget(item_data_cache_.display_data_->thumbnail,
				text_manager_cache_->GetRuneNameText(rune_data_cache_.set_type),
				//IKTODO: EDGE대신 룬 요약 텍스트 삽입.
				text_manager_cache_->GetRuneSetBonusText(rune_data_cache_.set_type, ERuneSetBonusType::Edge),
				rune_data_cache_.set_type);
	}
}

void URuneSlotWidget::SetImageTexture()
{
	Super::SetImageTexture();
	image_->SetBrushFromTexture(rune_data_cache_.item_data_.display_data_->thumbnail);
}

void URuneSlotWidget::ClearData()
{
	Super::ClearData();
	rune_data_cache_ = FRuneData();
}
