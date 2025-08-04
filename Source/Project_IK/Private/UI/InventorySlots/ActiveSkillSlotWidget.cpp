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
#include "Internationalization/StringTableCore.h"
#include "UI/InventoryWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Managers/DataTableManager.h"
#include "Structs/CharacterData.h"
#include "WorldSettings/IKGameInstance.h"

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
			Swap(casted_slot->item_data_cache_, item_data_cache_);
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
	if (is_empty_ == false)
	{
		image_->SetBrushFromTexture(active_skill_data_cache_.item_data_.display_data_->thumbnail);
	}
}

void UActiveSkillSlotWidget::ClearData()
{
	Super::ClearData();
	active_skill_data_cache_ = FActiveSkillData();
}

FText UActiveSkillSlotWidget::BuildDetailString()
{
	FText base = Super::BuildDetailString();
	FText final_text;
	//영웅에게 장착되어 있다면 총 데미지를 계산해야 한다.
	if (is_board_slot_ && hero_type_ != EHeroType::INVALID)
	{
		auto data_table_manager_ = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GetDataTableManager();
		const FCharacterData& cur_data = data_table_manager_->GetCharacterData(HeroTypeToCharacterType(hero_type_));
		FFormatNamedArguments args;
		args.Add("val", FText::AsNumber(cur_data.status_data_.skill_power_ * active_skill_data_cache_.skill_power_ratio_));

		final_text = FText::Format(base, args);
	}
	//영웅에게 장착되어 있지 않다면, 스킬 계수만 보여저야 한다.
	else
	{
		//1. 먼저 value에 해당하는 string을 format을 통해 조립한다.
		FText stat_text = FText::FromStringTable("/Game/StringTables/Status", "SkillPower");
		FText val_base = FText::FromString("{sp} x {stat}");
		FFormatNamedArguments val_args;
		val_args.Add("sp", FText::AsNumber(active_skill_data_cache_.skill_power_ratio_));
		val_args.Add("stat", stat_text);

		FText::Format(val_base, val_args);
		
		//2. base를 detail의 val에 넣는다.
		FFormatNamedArguments args;
		args.Add("val", FText::Format(val_base, val_args));
		final_text = FText::Format(base, args);
	}
	return final_text;
}
