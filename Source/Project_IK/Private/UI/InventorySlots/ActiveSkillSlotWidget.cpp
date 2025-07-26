/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.1.2025
Summary : Source file for Active skill slot Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "UI/InventorySlots/ActiveSkillSlotWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"
#include "UI/InventoryWidget.h"

void UActiveSkillSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
	slot_type_ = EInventorySlotType::ActiveSkill;
}

void UActiveSkillSlotWidget::SetActiveSkillSlotData(FActiveSkillData active_skill_data)
{
	is_empty_ = false;
	active_skill_data_cache_ = active_skill_data;
	item_data_cache_ = active_skill_data_cache_.item_data_;
	SetImageTexture();
}

FReply UActiveSkillSlotWidget::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry,
	const FPointerEvent& InMouseEvent)
{
	inventory_widget_cache_->SetHighlightVisibility(EGearType::ActiveSkill, ESlateVisibility::Visible);
	return Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);
}

bool UActiveSkillSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                          UDragDropOperation* InOperation)
{
	if (Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation))
	{
		auto casted_slot = Cast<UActiveSkillSlotWidget>(InOperation->Payload);
		if (casted_slot->is_board_slot_)
		{
			Swap(casted_slot->active_skill_data_cache_, active_skill_data_cache_);
			Swap(casted_slot->is_empty_, is_empty_);
			SetImageTexture();
			casted_slot->SetImageTexture();
		}
		else
		{
			if (inventory_widget_cache_->CheckDuplicatedActiveSkill(casted_slot->GetStoredActiveSkillData().type_) == false)
			{
				if (is_empty_ == false)
				{
					inventory_widget_cache_->AddToRewardContainer(this);
				}
				SetActiveSkillSlotData(casted_slot->active_skill_data_cache_);
				inventory_widget_cache_->RemoveFromRewardContainer(casted_slot);
			}
		}
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
	image_->SetBrushFromTexture(active_skill_data_cache_.item_data_.display_data_->thumbnail);
}

void UActiveSkillSlotWidget::ClearData()
{
	Super::ClearData();
	active_skill_data_cache_ = FActiveSkillData();
}
