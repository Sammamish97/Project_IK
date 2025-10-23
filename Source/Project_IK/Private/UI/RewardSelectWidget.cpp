/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.5.2025
Summary : Source file for Reward Select Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/RewardSelectWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CheckBox.h"
#include "Components/Image.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "UI/EquipmentRewardWidget.h"
#include "Managers/TextManager.h"

#include "Subsystems/AudioManagerSubsystem.h"

void URewardSelectWidget::NativeConstruct()
{
	Super::NativeConstruct();
	check_box_->OnCheckStateChanged.AddDynamic(this, &URewardSelectWidget::OnCheckBoxClicked);
	UIKGameInstance* instance = Cast<UIKGameInstance>(GetGameInstance());
	text_manager_cache_ = instance->GetTextManager();
}

void URewardSelectWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	switch (reward_data_.gear_type_)
	{
	case EGearType::ActiveSkill:
		{
			equipment_reward_widget_cache_->CreateActiveSkillPopupWidget(reward_data_.active_skill_data_.thumbnail_,
						text_manager_cache_->GetActiveSkillNameText(reward_data_.active_skill_data_.type_),
						reward_data_.active_skill_data_.BuildDetailText(GetWorld()),
						reward_data_.active_skill_data_.cool_time_);
		}
		break;

	case EGearType::PassiveSkill:
		equipment_reward_widget_cache_->CreatePassiveSkillPopupWidget(reward_data_.passive_skill_data_.thumbnail_,
			text_manager_cache_->GetPassiveSkillNameText(reward_data_.passive_skill_data_.type_),
			text_manager_cache_->GetPassiveSkillDetailText(reward_data_.passive_skill_data_.type_));
		break;

	case EGearType::Weapon:
		equipment_reward_widget_cache_->CreateWeaponPopupWidget(reward_data_.weapon_data_.thumbnail_,
			text_manager_cache_->GetWeaponNameText(reward_data_.weapon_data_.type_),
			text_manager_cache_->GetWeaponDetailText(reward_data_.weapon_data_.type_),
			reward_data_.weapon_data_.status_data_);
		break;

	case EGearType::Rune:
		equipment_reward_widget_cache_->CreateRunePopupWidget(reward_data_.rune_data_.thumbnail_,
				text_manager_cache_->GetRuneNameText(reward_data_.rune_data_.set_type),
				text_manager_cache_->GetRuneDetail(reward_data_.rune_data_.set_type),
				reward_data_.rune_data_.set_type);
		break;
	default:
		break;
	}
}

void URewardSelectWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	equipment_reward_widget_cache_->RemovePopupWidget();
}

void URewardSelectWidget::SetRewardData(const FActiveSkillData& data)
{
	reward_data_.gear_type_ = EGearType::ActiveSkill;
	reward_data_.active_skill_data_ = data;
	
	thumbnail_->SetBrushFromTexture(reward_data_.active_skill_data_.thumbnail_);
}

void URewardSelectWidget::SetRewardData(const FPassiveSkillData& data)
{
	reward_data_.gear_type_ = EGearType::PassiveSkill;
	reward_data_.passive_skill_data_ = data;

	thumbnail_->SetBrushFromTexture(reward_data_.passive_skill_data_.thumbnail_);
}

void URewardSelectWidget::SetRewardData(const FRuneData& data)
{
	reward_data_.gear_type_ = EGearType::Rune;
	reward_data_.rune_data_ = data;
	
	rune_idx_border_->SetVisibility(ESlateVisibility::HitTestInvisible);
	rune_idx_text_->SetVisibility(ESlateVisibility::HitTestInvisible);
	rune_idx_text_->SetText(FText::AsNumber(reward_data_.rune_data_.slot_number));

	thumbnail_->SetBrushFromTexture(reward_data_.rune_data_.thumbnail_);
}

void URewardSelectWidget::SetRewardData(const FWeaponData& data)
{
	reward_data_.gear_type_ = EGearType::Weapon;
	reward_data_.weapon_data_ = data;

	thumbnail_->SetBrushFromTexture(reward_data_.weapon_data_.thumbnail_);
}

void URewardSelectWidget::SetEquipmentWidgetCache(UEquipmentRewardWidget* equipment_widget_ptr)
{
	equipment_reward_widget_cache_ = equipment_widget_ptr;
}

const FRewardData& URewardSelectWidget::GetRewardData()
{
	return reward_data_;
}

void URewardSelectWidget::OnCheckBoxClicked(bool checked)
{
	if (checked)
	{
		UAudioManagerSubsystem::Get(this)->Play2D(EAudioType::UI_Confirm);
		equipment_reward_widget_cache_->IncreaseSelectedCounter();
	}
	else
	{
		UAudioManagerSubsystem::Get(this)->Play2D(EAudioType::UI_Deny);
		equipment_reward_widget_cache_->DecreaseSelectedCounter();
	}
}

bool URewardSelectWidget::GetIsChecked()
{
	return check_box_->IsChecked();
}