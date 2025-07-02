/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.1.2025
Summary : Header file for Active skill slot Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "InventorySlot.h"
#include "Structs/ActiveSkillData.h"
#include "ActiveSkillSlotWidget.generated.h"

UCLASS()
class PROJECT_IK_API UActiveSkillSlotWidget : public UInventorySlot
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	void SetActiveSkillSlotData(FActiveSkillData active_skill_data);
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	FActiveSkillData GetStoredActiveSkillData();
	virtual void SetImageTexture() override;
	
private:
	FActiveSkillData active_skill_data_cache_;
};
