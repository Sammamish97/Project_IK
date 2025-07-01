/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.1.2025
Summary : Source file for Passive skill Slot Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "UI/PassiveSkillSlotWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void UPassiveSkillSlotWidget::SetPassiveSkillSlotData(FPassiveSkillData passive_skill_data)
{
	passive_skill_data_cache_ = passive_skill_data;
	slot_type_ = EInventorySlotType::PassiveSkill;
}

bool UPassiveSkillSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                           UDragDropOperation* InOperation)
{
	if (Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation))
	{
		//IKTODO: Hero가 동일한 Passive Skill를 이미 장착하고 있는지 확인.
		auto casted_slot = Cast<UPassiveSkillSlotWidget>(InOperation->Payload);
		Swap(casted_slot->passive_skill_data_cache_, passive_skill_data_cache_);
		SetImageTexture();
		casted_slot->SetImageTexture();
		return true;
	}
	return false;
}

FPassiveSkillData UPassiveSkillSlotWidget::GetStoredPassiveSkillData()
{
	return passive_skill_data_cache_;
}
