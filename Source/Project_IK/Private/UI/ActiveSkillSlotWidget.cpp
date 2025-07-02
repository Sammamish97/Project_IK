/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.1.2025
Summary : Source file for Active skill slot Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "UI/ActiveSkillSlotWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"

void UActiveSkillSlotWidget::SetActiveSkillSlotData(FActiveSkillData active_skill_data)
{
	active_skill_data_cache_ = active_skill_data;
	slot_type_ = EInventorySlotType::ActiveSkill;
}

bool UActiveSkillSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                          UDragDropOperation* InOperation)
{
	if (Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation))
	{
		auto casted_slot = Cast<UActiveSkillSlotWidget>(InOperation->Payload);
		//IKTODO: 다른 Hero들 중 현재 장착하려는 Active Skill를 이미 장착하려는 Hero가 없어야 함.
		Swap(casted_slot->active_skill_data_cache_, active_skill_data_cache_);
		SetImageTexture();
		casted_slot->SetImageTexture();
		return true;
	}
	return false;
}

FActiveSkillData UActiveSkillSlotWidget::GetStoredActiveSkillData()
{
	return active_skill_data_cache_;
}

void UActiveSkillSlotWidget::SetImageTexture()
{
	Super::SetImageTexture();
	image_->SetBrushFromTexture(active_skill_data_cache_.item_data_.thumbnail);
}
