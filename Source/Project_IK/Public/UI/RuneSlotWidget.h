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
#include "InventorySlot.h"
#include "Blueprint/UserWidget.h"
#include "Structs/RuneSetData.h"
#include "RuneSlotWidget.generated.h"
class URuneBoardWidget;
class UImage;
UCLASS()
class PROJECT_IK_API URuneSlotWidget : public UInventorySlot
{
	GENERATED_BODY()
public:
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	void SetRuneSetSlotData(const FRuneData& rune_data);
	void SetRuneSetSlotData(EInventorySlotType slot_type);
	const FRuneData& GetStoredRuneData();
	virtual void SetImageTexture() override;

private:
	FRuneData rune_data_cache_;
};