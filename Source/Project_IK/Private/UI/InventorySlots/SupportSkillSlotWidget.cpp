/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.4.2025
Summary : Header file for Support skill Slot Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/InventorySlots/SupportSkillSlotWidget.h"

#include "Blueprint/DragDropOperation.h"
#include "Components/Image.h"
#include "UI/InventoryWidget.h"

void USupportSkillSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
	slot_type_ = EInventorySlotType::SupportSkill;
}

bool USupportSkillSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	if (Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation))
	{
		auto casted_slot = Cast<USupportSkillSlotWidget>(InOperation->Payload);
		if (casted_slot->is_board_slot_)
		{
			Swap(casted_slot->support_skill_data_cache_, support_skill_data_cache_);
			Swap(casted_slot->is_empty_, is_empty_);
			SetImageTexture();
			casted_slot->SetImageTexture();
		}
		else
		{
			if (is_empty_ == false)
			{
				inventory_widget_cache_->AddToRewardContainer(this);
			}
			SetSupportSkillSlotData(casted_slot->support_skill_data_cache_);
			inventory_widget_cache_->RemoveFromRewardContainer(casted_slot);
		}
		return true;
	}
	return false;
}

void USupportSkillSlotWidget::SetSupportSkillSlotData(FSupportSkillData support_skill_data)
{
	is_empty_ = false;
	support_skill_data_cache_ = support_skill_data;
	SetImageTexture();
}

FSupportSkillData USupportSkillSlotWidget::GetStoredSupportSkillData()
{
	return support_skill_data_cache_;
}

void USupportSkillSlotWidget::SetImageTexture()
{
	Super::SetImageTexture();
	image_->SetBrushFromTexture(support_skill_data_cache_.item_data_.thumbnail);
}
