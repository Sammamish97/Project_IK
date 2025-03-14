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
#include "Components/Button.h"
#include "Components/Image.h"
#include "Kismet/GameplayStatics.h"
#include "UI/RuneStorageWidget.h"
#include "Managers/InventoryManager.h"
#include "UI/SlotDragDropImage.h"
#include "WorldSettings/IKGameInstance.h"

class URuneStorageWidget;
class UIKGameInstance;

void URuneSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
	button_->OnClicked.AddDynamic(this, &URuneSlotWidget::OnClicked);
}

void URuneSlotWidget::NativeDestruct()
{
	Super::NativeDestruct();
	UE_LOG(LogTemp, Display, TEXT("URuneSlotWidget::NativeDestruct"));
	button_->OnClicked.Clear();
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
	
	OutOperation = dragdrop_operation;

	if (is_board_slot_)
	{
		rune_storage_widget_cache_->UpdateRuneStorage();
		rune_storage_widget_cache_->LoadRuneStorage(GetRuneData().slot_number);
	}
}

bool URuneSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                   UDragDropOperation* InOperation)
{
	//TODO: 코드의 중복이 많다. if문의 결합, 혹은 구조의 변환을 통해 반복되는 코드를 줄여보자.
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	if(InOperation->Payload == this) return false;
	TObjectPtr<URuneSlotWidget> slot_from = Cast<URuneSlotWidget>(InOperation->Payload);
	//1. 둘 다 Board면 반드시 slot_num이 다르기 때문에 교체가 불가능 하다.
	if (is_board_slot_ && slot_from->is_board_slot_)
	{
		return false;
	}
	
	//2. 둘다 storage에 있다면 둘다 동일한 slot num이 보장되므로 swap한다.
	if (is_board_slot_ == false && slot_from->is_board_slot_ == false)
	{
		Swap(rune_data_, slot_from->rune_data_);
		SetImageTexture();
		slot_from->SetImageTexture();
		return true;
	}
	
	//3. board에서 storage로 오는 경우, 현재 선택된 board의 slot num에 맞춰 storage를 띄워준다.
	if (is_board_slot_ == false && slot_from->is_board_slot_)
	{
		Swap(rune_data_, slot_from->rune_data_);
		SetImageTexture();
		slot_from->SetImageTexture();
		return true;
	}
	
	//4. storage에서 board로 가는 경우, slot num을 확인해야 한다.
	if (is_board_slot_ && slot_from->is_board_slot_ == false)
	{
		if (slot_from->rune_data_.slot_number == rune_data_.slot_number)
		{
			Swap(rune_data_, slot_from->rune_data_);
			SetImageTexture();
			slot_from->SetImageTexture();
			return true;
		}
	}
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

FRuneData URuneSlotWidget::GetRuneData()
{
	return rune_data_;
}

bool URuneSlotWidget::IsBoardSlot()
{
	return is_board_slot_;
}

void URuneSlotWidget::SetIsBoardSlot(bool is_board_slot)
{
	is_board_slot_ = is_board_slot;
}


void URuneSlotWidget::InitRuneSlot(TObjectPtr<URuneStorageWidget> rune_storage_ptr)
{
	rune_storage_widget_cache_ = rune_storage_ptr;
}

void URuneSlotWidget::OnClicked()
{
	if (is_board_slot_)
	{
		rune_storage_widget_cache_->UpdateRuneStorage();
		rune_storage_widget_cache_->LoadRuneStorage(rune_data_.slot_number);
	}
}