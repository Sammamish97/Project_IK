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
#include "UI/SlotDragDropImage.h"

FReply URuneSlotWidget::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);
	if(InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		FEventReply ReplyResult = UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton);
		return ReplyResult.NativeReply;
	}
	return FReply::Unhandled();
}

void URuneSlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	if(is_empty_ == true) return;
	
	UDragDropOperation* dragdrop_operation = UWidgetBlueprintLibrary::CreateDragDropOperation(UDragDropOperation::StaticClass());
	dragdrop_operation->Payload = this;
	
	auto dragged_image_widget = CreateWidget(GetWorld(), dragdrop_image_class_);
	Cast<USlotDragDropImage>(dragged_image_widget)->image_->
	SetBrushFromTexture(UWidgetBlueprintLibrary::GetBrushResourceAsTexture2D(image_->GetBrush()));
	
	dragdrop_operation->DefaultDragVisual = dragged_image_widget;
	dragdrop_operation->Pivot = EDragPivot::CenterCenter;
	
	OutOperation = dragdrop_operation;}

bool URuneSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	if(InOperation->Payload == this) return false;
	TObjectPtr<URuneSlotWidget> slot_from = Cast<URuneSlotWidget>(InOperation->Payload);
	if (slot_from->slot_num_ == slot_num_)
	{
		Swap(rune_data_, slot_from->rune_data_);
		Swap(is_empty_, slot_from->is_empty_);
		SetImageTexture();
		slot_from->SetImageTexture();
		return true;
	}
	return false;
}

void URuneSlotWidget::ClearData()
{
	rune_data_ = FRuneData();
	is_empty_ = true;
	slot_num_ = 0;
	image_->SetBrushFromTexture(nullptr);
}

void URuneSlotWidget::SetImageTexture()
{
	if (is_empty_ == false)
	{
		image_->SetBrushFromTexture(rune_data_.thumbnail);
	}
}

void URuneSlotWidget::SetSlotNum(int32 num)
{
	slot_num_ = num;
}

void URuneSlotWidget::SetRuneData(FRuneData data)
{
	rune_data_ = data;
}
