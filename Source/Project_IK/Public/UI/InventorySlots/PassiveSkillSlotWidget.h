/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.1.2025
Summary : Header file for Passive skill Slot Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "InventorySlot.h"
#include "Structs/PassiveSkillData.h"
#include "PassiveSkillSlotWidget.generated.h"

UCLASS()
class PROJECT_IK_API UPassiveSkillSlotWidget : public UInventorySlot
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
	void SetPassiveSkillSlotData(const FPassiveSkillData& passive_skill_data);
	const FPassiveSkillData& GetStoredPassiveSkillData();
	virtual void SetImageTexture() override;
	virtual void ClearData() override;

private:
	FPassiveSkillData passive_skill_data_cache_;
};
