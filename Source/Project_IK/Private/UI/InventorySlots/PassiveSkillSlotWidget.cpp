/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.1.2025
Summary : Source file for Passive skill Slot Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "UI/InventorySlots/PassiveSkillSlotWidget.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"
#include "UI/InventoryWidget.h"

void UPassiveSkillSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();
	slot_type_ = EInventorySlotType::PassiveSkill;
}

void UPassiveSkillSlotWidget::SetHeroType(EHeroType hero_type)
{
	hero_type_ = hero_type;
}

void UPassiveSkillSlotWidget::SetPassiveSkillSlotData(const FPassiveSkillData& passive_skill_data)
{
	is_empty_ = false;
	passive_skill_data_cache_ = passive_skill_data;
	item_data_cache_ = passive_skill_data_cache_.item_data_;
	SetImageTexture();
}

FReply UPassiveSkillSlotWidget::NativeOnPreviewMouseButtonDown(const FGeometry& InGeometry,
	const FPointerEvent& InMouseEvent)
{
	inventory_widget_cache_->SetHighlightVisibility(EGearType::PassiveSkill, ESlateVisibility::Visible);
	return Super::NativeOnPreviewMouseButtonDown(InGeometry, InMouseEvent);
}

bool UPassiveSkillSlotWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                           UDragDropOperation* InOperation)
{
	//IKTODO: Hero가 동일한 Passive Skill를 이미 장착하고 있는지 확인.
	if (Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation))
	{
		auto casted_slot = Cast<UPassiveSkillSlotWidget>(InOperation->Payload);
		if (casted_slot->is_board_slot_)
		{
			Swap(casted_slot->passive_skill_data_cache_, passive_skill_data_cache_);
			Swap(casted_slot->is_empty_, is_empty_);
			SetImageTexture();
			casted_slot->SetImageTexture();
		}
		else
		{
			if (inventory_widget_cache_->CheckDuplicatedPassiveSkill(hero_type_, passive_skill_data_cache_.type_) == false)
			{
				if (is_empty_ == false)
				{
					inventory_widget_cache_->AddToRewardContainer(this);
				}
				SetPassiveSkillSlotData(casted_slot->passive_skill_data_cache_);
				inventory_widget_cache_->RemoveFromRewardContainer(casted_slot);
			}
		}
		return true;
	}
	return false;
}

const FPassiveSkillData& UPassiveSkillSlotWidget::GetStoredPassiveSkillData()
{
	return passive_skill_data_cache_;
}

void UPassiveSkillSlotWidget::SetImageTexture()
{
	Super::SetImageTexture();
	image_->SetBrushFromTexture(passive_skill_data_cache_.item_data_.display_data_->thumbnail);
}

void UPassiveSkillSlotWidget::ClearData()
{
	Super::ClearData();
	passive_skill_data_cache_ = FPassiveSkillData();
}
