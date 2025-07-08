/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.3.2025
Summary : Header file for Inventory Slot Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/ItemData.h"
#include "InventorySlot.generated.h"

class USlotDragDropImage;
class UInventoryWidget;

UCLASS()
class PROJECT_IK_API UInventorySlot : public UUserWidget
{
	GENERATED_BODY()
public:
	void InitInventorySlot(UInventoryWidget* widget_ptr, bool is_board_slot = true);
	virtual FReply NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	
	virtual void SetImageTexture();

	EInventorySlotType GetSlotType() const;
	virtual void ClearData();
	bool IsEmpty() const;
	bool IsBoardSlot() const;

protected:
	UPROPERTY()
	EInventorySlotType slot_type_ = EInventorySlotType::INVALID;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TSubclassOf<USlotDragDropImage> dragdrop_image_class_;

	UPROPERTY(Transient)
	TObjectPtr<UInventoryWidget> inventory_widget_cache_;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UImage> image_;
	
	FItemData item_data_cache_;

	bool is_empty_ = true;
	bool is_board_slot_ = true;
};
