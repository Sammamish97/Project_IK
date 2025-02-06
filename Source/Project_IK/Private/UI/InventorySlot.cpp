/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.06.2025
Summary : Source file for inventory slot widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/InventorySlot.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"

FReply UInventorySlot::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);
	if(InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		FEventReply ReplyResult = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
		return ReplyResult.NativeReply;
	}
	return FReply::Unhandled();
}

void UInventorySlot::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	// if(dp_data_.dp_type_==EDPType::Empty) return;
	//
	// UDPDragDropOperation* dragdrop_operation = Cast<UDPDragDropOperation>(UWidgetBlueprintLibrary::CreateDragDropOperation(dragdrop_class_));
	// dragdrop_operation->dragged_slot_data_ = this;
	//
	// auto dragged_image_widget = CreateWidget(GetWorld(), dragdrop_image_class_);
	//
	// Cast<UDPDragDropImage>(dragged_image_widget)->SetImage(dp_data_.dp_icon_);
	// dragdrop_operation->DefaultDragVisual = dragged_image_widget;
	// dragdrop_operation->Pivot = EDragPivot::CenterCenter;
	//
	// OutOperation = dragdrop_operation;
}

bool UInventorySlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	// UDPDragDropOperation* casted_operation = Cast<UDPDragDropOperation>(InOperation);
	// if(casted_operation->dragged_slot_data_ == this) return false;
	// if(slot_type_ == EDPSlotType::HeroPeriodic)
	// {
	// 	if(casted_operation->dragged_slot_data_->dp_data_.is_periodic_ == false)
	// 	{
	// 		return false;
	// 	}
	// }
	// if(slot_type_ == EDPSlotType::HeroGeneral)
	// {
	// 	if(casted_operation->dragged_slot_data_->dp_data_.is_periodic_ == true)
	// 	{
	// 		return false;
	// 	}
	// }
	// Swap(dp_data_, casted_operation->dragged_slot_data_->dp_data_);
	// SetImageTexture();
	// casted_operation->dragged_slot_data_->SetImageTexture();
	return true;
}

void UInventorySlot::ClearData()
{
	slot_data_ = FInventorySlotData();
	slot_type_ = EInventorySlotType::Inventory;
	image_->SetBrushFromTexture(nullptr);
}

void UInventorySlot::SetImageTexture()
{
	//image_->SetBrushFromTexture(dp_data_.dp_icon_);
}