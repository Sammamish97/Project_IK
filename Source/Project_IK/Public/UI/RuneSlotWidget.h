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
#include "RuneSlotWidget.generated.h"

UCLASS()
class PROJECT_IK_API URuneSlotWidget : public UUserWidget
{
	GENERATED_BODY()
private:
	virtual FReply NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
public:
	void ClearData();
	void SetImageTexture();
	void SetSlotNum(int32 num);
	
private:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	class UButton* button_;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	class UImage* image_;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TSubclassOf<UUserWidget> dragdrop_image_class_;
	
	UPROPERTY()
	bool is_empty_ = true;

	UPROPERTY()
	int32 slot_num_ = 0;
	
	UPROPERTY()
	FRuneData rune_data_ = FRuneData();
};
