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
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	void SetPassiveSkillSlotData(FPassiveSkillData passive_skill_data);
	FPassiveSkillData GetStoredPassiveSkillData();
	virtual void SetImageTexture() override;

private:
	FPassiveSkillData passive_skill_data_cache_;
};
