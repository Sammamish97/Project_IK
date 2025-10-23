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
#include "Managers/EventManager.h"
#include "InventorySlot.generated.h"

class USlotDragDropImage;
class UInventoryWidget;
class UTextManager;
class UImage;

UCLASS()
class PROJECT_IK_API UInventorySlot : public UUserWidget
{
	GENERATED_BODY()
public:
	void InitInventorySlot(UInventoryWidget* widget_ptr, bool is_board_slot = true, EHeroType hero_type = EHeroType::INVALID);

	virtual void NativeConstruct() override;
	virtual FReply NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	
	virtual void SetImageTexture();

	void SetIsReadOnly(bool is_read_only);
	void SetHighlightImageVisibility(ESlateVisibility visibility);

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

	UPROPERTY(Transient)
	TObjectPtr<UTextManager> text_manager_cache_;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> image_;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> highlight_image_;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UTexture2D> empty_image_;
	
	bool is_read_only_ = false;
	bool is_empty_ = true;
	bool is_board_slot_ = true;
	EHeroType hero_type_ = EHeroType::INVALID;
};
