/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.06.2025
Summary : Header file for inventory slot widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Managers/EnumCluster.h"
#include "Structs/InventorySlotData.h"
#include "InventorySlot.generated.h"


UCLASS()
class PROJECT_IK_API UInventorySlot : public UUserWidget
{
	GENERATED_BODY()
private:
	virtual FReply NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
public:
	void ClearData();
	void SetImageTexture();
	
private:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<class UButton> button_;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<class UImage> image_;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TSubclassOf<UUserWidget> dragdrop_image_class_;
	
public:
	//SlotType은 현재 slot이 어떤 장비를 위한 slot인지 판별하기 위한 Enum이다.
	EInventorySlotType slot_type_= EInventorySlotType::INVALID;
	FInventorySlotData slot_data_;
	int grid_idx_;
};
