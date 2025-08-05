/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.3.2025
Summary : Source file for Inventory Slot Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "UI/InventorySlots/InventorySlot.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"
#include "UI/InventoryWidget.h"
#include "UI/SlotDragDropImage.h"
#include "Blueprint/WidgetLayoutLibrary.h"

void UInventorySlot::InitInventorySlot(UInventoryWidget* widget_ptr, bool is_board_slot, EHeroType hero_type)
{
	inventory_widget_cache_ = widget_ptr;
	is_board_slot_ = is_board_slot;
	hero_type_ = hero_type;
	
	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	text_manager_cache_ = game_instance->GetTextManager();
}

void UInventorySlot::NativeConstruct()
{
	Super::NativeConstruct();
	highlight_image_->SetVisibility(ESlateVisibility::Hidden);
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
	inventory_widget_cache_->RemoveHighlight();
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	if (auto casted_inventory_slot = Cast<UInventorySlot>(InOperation->Payload))
	{
		//Drop을 할 수 있는 조건은 다음과 같다.
		//1. Board가 아닌 slot에는 drop할 수 없다.
		//2. Drag하는 slot과 drop하는 slot이 동일해야 한다.
		//3. 자기자신을 drop할 수 없다.
		if (is_board_slot_ && casted_inventory_slot->slot_type_ == slot_type_ && InOperation->Payload != this)
		{
			return true;
		}
	}
	return false;
}

void UInventorySlot::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	inventory_widget_cache_->RemoveHighlight();
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);
}

void UInventorySlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	if (is_empty_ == false)
	{
		inventory_widget_cache_->CreatePopupWidget(item_data_cache_.display_data_->thumbnail,
			text_manager_cache_->GetNameText(item_data_cache_.display_data_->text_key_),
			text_manager_cache_->GetDetailText(item_data_cache_.display_data_->text_key_));
	}
}

FReply UInventorySlot::NativeOnMouseMove(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseMove(InGeometry, InMouseEvent);
	float pos_x, pos_y;
	UWidgetLayoutLibrary::GetMousePositionScaledByDPI(inventory_widget_cache_->GetOwningPlayer(), pos_x, pos_y);
	inventory_widget_cache_->SetPopupWidgetPos({pos_x, pos_y});
	return FReply::Unhandled();
}

void UInventorySlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	inventory_widget_cache_->RemovePopupWidget();
}

void UInventorySlot::ClearData()
{
	is_empty_ = true;
	item_data_cache_ = FItemData();
	//IKTODO: 이후 비워두는 것이 아닌, 빈칸 텍스쳐를 띄워야 함.
	image_->SetBrushFromTexture(nullptr);
}

void UInventorySlot::SetImageTexture()
{
	if (is_empty_)
	{
		image_->SetBrushFromTexture(nullptr);
	}
}

void UInventorySlot::SetHighlightImageVisibility(ESlateVisibility visibility)
{
	highlight_image_->SetVisibility(visibility);
}

EInventorySlotType UInventorySlot::GetSlotType() const
{
	return slot_type_;
}

bool UInventorySlot::IsEmpty() const
{
	return is_empty_;
}

bool UInventorySlot::IsBoardSlot() const
{
	return is_board_slot_;
}
