/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 3.10.2025
Summary : Header file for Rune Slot widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/RuneData.h"
#include "Structs/RuneSlotData.h"
#include "RuneSlotWidget.generated.h"

UCLASS()
class PROJECT_IK_API URuneSlotWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	virtual FReply NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
public:
	void InitRuneStorageData(TObjectPtr<class URuneStorageWidget> rune_storage_ptr);
	void InitRuneBoardData(TObjectPtr<class URuneBoardWidget> rune_board_ptr);
	void ClearData();
	bool IsBoardSlot();
	bool IsEmptySlot();
	void SetSelectedImageVisibility(bool value);
	void SetImageTexture();
	void SetIsBoardSlot(bool is_board_slot);
	void SetRuneData(FRuneData data);
	FRuneSlotData GetRuneSlotData();
	FRuneData GetRuneData();

	UFUNCTION()
	void OnClicked();
	
private:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<class UImage> selected_image_;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<class UButton> button_;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<class UImage> image_;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TSubclassOf<UUserWidget> dragdrop_image_class_;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true))
	TObjectPtr<class URuneStorageWidget> rune_storage_widget_cache_;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true))
	TObjectPtr<class URuneBoardWidget> rune_board_widget_cache_;

	FRuneSlotData rune_slot_data_;
	bool is_board_slot_ = false;
	int32 rune_slot_idx_ = 0;
};
