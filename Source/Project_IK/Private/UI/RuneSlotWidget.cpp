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
#include "Managers/InventoryManager.h"
#include "UI/RuneStorageWidget.h"
#include "UI/RuneBoardWidget.h"
#include "UI/SlotDragDropImage.h"
#include "WorldSettings/IKGameInstance.h"

class UIKGameInstance;

void URuneSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
	selected_image_->SetVisibility(ESlateVisibility::Hidden);
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
	if(rune_slot_data_.is_empty == true) return;
	
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
		rune_storage_widget_cache_->LoadRuneStorage(rune_slot_data_.rune_data.slot_number);
		rune_board_widget_cache_->SetSelectedBorder(rune_slot_data_.rune_data.slot_number);
		rune_board_widget_cache_->TurnOnSetBonusEffect();
	}
}

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
	
	//2. 둘다 storage에 있다면 둘다 동일한 slot num이 보장되므로 swap한다.
	if (is_board_slot_ == false && slot_from->is_board_slot_ == false)
	{
		Swap(rune_slot_data_, slot_from->rune_slot_data_);
		SetImageTexture();
		slot_from->SetImageTexture();
		return true;
	}
	
	//3. board에서 storage로 오는 경우, 현재 선택된 board의 slot num에 맞춰 storage를 띄워준다.
	if (is_board_slot_ == false && slot_from->is_board_slot_)
	{
		Swap(rune_slot_data_, slot_from->rune_slot_data_);
		SetImageTexture();
		slot_from->SetImageTexture();
		rune_board_widget_cache_->TurnOnSetBonusEffect();
		return true;
	}
	
	//4. storage에서 board로 가는 경우, slot num을 확인해야 한다.
	if (is_board_slot_ && slot_from->is_board_slot_ == false)
	{
		if (slot_from->rune_slot_idx_ == rune_slot_idx_)
		{
			Swap(rune_slot_data_, slot_from->rune_slot_data_);
			SetImageTexture();
			slot_from->SetImageTexture();
			rune_board_widget_cache_->TurnOnSetBonusEffect();
			return true;
		}
	}
	return false;
}

void URuneSlotWidget::ClearData()
{
	rune_slot_data_ = FRuneSlotData();
	image_->SetBrushFromTexture(nullptr);
}

void URuneSlotWidget::SetImageTexture()
{
	if (rune_slot_data_.is_empty)
	{
		image_->SetBrushFromTexture(nullptr);
	}
	else
	{
		TObjectPtr<UIKGameInstance> ik_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		image_->SetBrushFromTexture(ik_instance->GetDataTableManager()->GetRuneSetThumbnail(rune_slot_data_.rune_data.set_type));
	}
}

void URuneSlotWidget::SetRuneData(FRuneData data)
{
	rune_slot_data_.rune_data = data;
	rune_slot_data_.is_empty = false;
}

void URuneSlotWidget::SetRuneSlotIndex(int32 index)
{
	rune_slot_idx_ = index;
}

FRuneSlotData URuneSlotWidget::GetRuneSlotData()
{
	return rune_slot_data_;
}

FRuneData URuneSlotWidget::GetRuneData()
{
	return rune_slot_data_.rune_data;
}

bool URuneSlotWidget::IsEmptySlot()
{
	return rune_slot_data_.is_empty;
}

bool URuneSlotWidget::IsBoardSlot()
{
	return is_board_slot_;
}

void URuneSlotWidget::SetSelectedImageVisibility(bool value)
{
	if (value)
	{
		selected_image_->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		selected_image_->SetVisibility(ESlateVisibility::Hidden);
	}
}

void URuneSlotWidget::SetIsBoardSlot(bool is_board_slot)
{
	is_board_slot_ = is_board_slot;
}

void URuneSlotWidget::InitRuneStorageData(TObjectPtr<class URuneStorageWidget> rune_storage_ptr)
{
	rune_storage_widget_cache_ = rune_storage_ptr;
}

void URuneSlotWidget::InitRuneBoardData(TObjectPtr<class URuneBoardWidget> rune_board_ptr)
{
	rune_board_widget_cache_ = rune_board_ptr;
}

void URuneSlotWidget::OnClicked()
{
	if (is_board_slot_)
	{
		rune_storage_widget_cache_->UpdateRuneStorage();
		rune_storage_widget_cache_->LoadRuneStorage(rune_slot_idx_);
		rune_board_widget_cache_->SetSelectedBorder(rune_slot_idx_);
		SetSelectedImageVisibility(true);
	}
}