/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.3.2025
Summary : Source file for Inventory Slot Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/#include "UI/InventorySlot.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"
#include "UI/SlotDragDropImage.h"

void UInventorySlot::SetInventoryWidgetCache(UInventoryWidget* widget_ptr)
{
	inventory_widget_cache_ = widget_ptr;
}

FReply UInventorySlot::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
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
	if (is_empty_) return;

	UDragDropOperation* dragdrop_operation = UWidgetBlueprintLibrary::CreateDragDropOperation(UDragDropOperation::StaticClass());
	dragdrop_operation->Payload = this;

	auto dragged_image_widget = CreateWidget(GetWorld(), dragdrop_image_class_);
	Cast<USlotDragDropImage>(dragged_image_widget)->image_->
		SetBrushFromTexture(UWidgetBlueprintLibrary::GetBrushResourceAsTexture2D(image_->GetBrush()));

	dragdrop_operation->DefaultDragVisual = dragged_image_widget;
	dragdrop_operation->Pivot = EDragPivot::CenterCenter;

	OutOperation = dragdrop_operation;
}

//이 함수는 기본적인 swap가능 여부를 확인한다. 실제 Drop이 일어나는 상황은 이 함수를 상속한 자식 함수에서 구현되어야 한다.
bool UInventorySlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	if (auto casted_inventory_slot = Cast<UInventorySlot>(InOperation->Payload))
	{
		//Drop하는 Widget이 자기자신이 아니고 Type이 같으면 Swap이 가능하다.
		if (casted_inventory_slot->slot_type_ == slot_type_ && InOperation->Payload != this)
		{
			return true;
		}
	}
	return false;
}

void UInventorySlot::ClearData()
{
	image_->SetBrushFromTexture(nullptr);
}

void UInventorySlot::SetImageTexture()
{
	if (is_empty_)
	{
		image_->SetBrushFromTexture(nullptr);
	}
}

bool UInventorySlot::IsEmpty() const
{
	return is_empty_;
}
