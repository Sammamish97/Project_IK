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
#include "Kismet/GameplayStatics.h"
#include "Managers/EquipManager.h"
#include "UI/DPDragDropImage.h"
#include "UI/SlotDragDropImage.h"
#include "WorldSettings/IKGameInstance.h"

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
	if(slot_data_.is_empty == true) return;
	
	UDragDropOperation* dragdrop_operation = UWidgetBlueprintLibrary::CreateDragDropOperation(UDragDropOperation::StaticClass());
	dragdrop_operation->Payload = this;
	
	auto dragged_image_widget = CreateWidget(GetWorld(), dragdrop_image_class_);
	Cast<USlotDragDropImage>(dragged_image_widget)->image_->
	SetBrushFromTexture(UWidgetBlueprintLibrary::GetBrushResourceAsTexture2D(image_->GetBrush()));
	
	dragdrop_operation->DefaultDragVisual = dragged_image_widget;
	dragdrop_operation->Pivot = EDragPivot::CenterCenter;
	
	OutOperation = dragdrop_operation;
}

bool UInventorySlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	if(InOperation->Payload == this) return false;

	UInventorySlot* slot_from = Cast<UInventorySlot>(InOperation->Payload);
	if(slot_type_ == EInventorySlotType::Armor)
	{
		if(slot_from->slot_data_.gear_type == EGearType::Armor)
		{
			return false;
		}
	}
	if(slot_type_ == EInventorySlotType::Trinket)
	{
		if(slot_from->slot_data_.gear_type == EGearType::Trinket)
		{
			return false;
		}
	}
	Swap(slot_data_, slot_from->slot_data_);
	SetImageTexture();
	slot_from->SetImageTexture();
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
	if(slot_data_.is_empty == true)
	{
		image_->SetBrushFromTexture(nullptr);
		return;
	}
	//TODO: 마음에 안드는 부분이다. 더 좋은 방법이 있을것이다.
	UIKGameInstance* instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	UEquipManager* equip_manager = instance->GetEquipManager();
	UTexture2D* new_texture = nullptr;
	if(slot_data_.gear_type == EGearType::Armor)
	{
		new_texture = equip_manager->GetArmorData(slot_data_.armor_type).thumbnail;
	}
	else if(slot_data_.gear_type == EGearType::Trinket)
	{
		new_texture = equip_manager->GetTrinketData(slot_data_.trinket_type).thumbnail;
	}
	//
	image_->SetBrushFromTexture(new_texture);
}