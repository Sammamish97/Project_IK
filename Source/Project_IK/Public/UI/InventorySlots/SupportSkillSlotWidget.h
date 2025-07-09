/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.4.2025
Summary : Source file for Support skill Slot Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once
#include "CoreMinimal.h"
#include "InventorySlot.h"
#include "Structs/SupportSkillData.h"
#include "SupportSkillSlotWidget.generated.h"
UCLASS()
class PROJECT_IK_API USupportSkillSlotWidget : public UInventorySlot
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	void SetSupportSkillSlotData(FSupportSkillData passive_skill_data);
	FSupportSkillData GetStoredSupportSkillData();
	virtual void SetImageTexture() override;
	virtual void ClearData() override;

private:
	FSupportSkillData support_skill_data_cache_;
};
