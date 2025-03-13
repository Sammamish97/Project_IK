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
#include "Kismet/GameplayStatics.h"
#include "UI/SlotDragDropImage.h"
#include "WorldSettings/IKGameInstance.h"

class UIKGameInstance;

void URuneSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

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
	if(rune_data_.is_empty == true) return;
	
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
	//1. 둘 다 Board면 반드시 slot_num이 다르기 때문에 교체가 불가능 하다.
	if (is_board_slot_ && slot_from->is_board_slot_)
	{
		return false;
	}
	//2. 둘다 storage에 있다면 slot_num과 상관 없이 swap 가능하다.
	if (is_board_slot_ == false && slot_from->is_board_slot_ == false)
	{
		Swap(rune_data_, slot_from->rune_data_);
		SetImageTexture();
		slot_from->SetImageTexture();
		return true;
	}
	//3. 둘중 하나만 board라면, 만약 시작점이 storage이고 도착점이 board라면 slot num을 확인해야 한다.
	if (slot_from->rune_data_.slot_number == rune_data_.slot_number)
	{
		Swap(rune_data_, slot_from->rune_data_);
		SetImageTexture();
		slot_from->SetImageTexture();
		return true;
	}

	//4. 둘중 하나만 board라면, 만약 시작점이 board이고, 도착점이 storage라면 케이스가 2가지가 있다.
	//a. 인벤토리가 비어있을 수 있다.
	//b. 룬이 있고 slot num이 동일할 수 있다.
	//c. 룬이 있고 slot num이 다를 수 있다.
	return false;
}

void URuneSlotWidget::ClearData()
{
	rune_data_ = FRuneData();
	image_->SetBrushFromTexture(nullptr);
}

void URuneSlotWidget::SetImageTexture()
{
	if (rune_data_.is_empty)
	{
		image_->SetBrushFromTexture(nullptr);
	}
	else
	{
		TObjectPtr<UIKGameInstance> ik_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		image_->SetBrushFromTexture(ik_instance->GetDataTableManager()->GetRuneSetThumbnail(rune_data_.set_type));
	}
}

void URuneSlotWidget::SetRuneData(FRuneData data)
{
	rune_data_ = data;
}

bool URuneSlotWidget::IsBoardSlot()
{
	return is_board_slot_;
}

void URuneSlotWidget::SetIsBoardSlot(bool is_board_slot)
{
	is_board_slot_ = is_board_slot;
}
