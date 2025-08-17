/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.5.2025
Summary : Source file for Reward Select Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/RewardSelectWidget.h"
#include "Components/CheckBox.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "UI/EquipmentRewardWidget.h"

void URewardSelectWidget::NativeConstruct()
{
	Super::NativeConstruct();
	check_box_->OnCheckStateChanged.AddDynamic(this, &URewardSelectWidget::OnCheckBoxClicked);
	check_image_->SetVisibility(ESlateVisibility::Hidden);
}

void URewardSelectWidget::SetRewardData(const FActiveSkillData& data)
{
	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	UTextManager* text_manager = game_instance->GetTextManager();
	
	reward_data_.gear_type_ = EGearType::ActiveSkill;
	reward_data_.active_skill_data_ = data;
	
	thumbnail_->SetBrushFromTexture(reward_data_.active_skill_data_.item_data_.display_data_->thumbnail);
	name_->SetText(text_manager->GetActiveSkillNameText(reward_data_.active_skill_data_.item_data_.display_data_->text_key_));
	detail_->SetText(reward_data_.active_skill_data_.BuildDetailText(GetWorld()));
}

void URewardSelectWidget::SetRewardData(const FPassiveSkillData& data)
{
	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	UTextManager* text_manager = game_instance->GetTextManager();
	
	reward_data_.gear_type_ = EGearType::PassiveSkill;
	reward_data_.passive_skill_data_ = data;

	thumbnail_->SetBrushFromTexture(reward_data_.passive_skill_data_.item_data_.display_data_->thumbnail);
	name_->SetText(text_manager->GetActiveSkillNameText(reward_data_.passive_skill_data_.item_data_.display_data_->text_key_));
	detail_->SetText(text_manager->GetActiveSkillDetailText(reward_data_.passive_skill_data_.item_data_.display_data_->text_key_));
}

void URewardSelectWidget::SetRewardData(const FRuneData& data)
{
	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	UTextManager* text_manager = game_instance->GetTextManager();
	
	reward_data_.gear_type_ = EGearType::Rune;
	reward_data_.rune_data_ = data;

	thumbnail_->SetBrushFromTexture(reward_data_.rune_data_.item_data_.display_data_->thumbnail);
	name_->SetText(text_manager->GetActiveSkillNameText(reward_data_.rune_data_.item_data_.display_data_->text_key_));
	detail_->SetText(text_manager->GetActiveSkillDetailText(reward_data_.rune_data_.item_data_.display_data_->text_key_));
}

void URewardSelectWidget::SetRewardData(const FWeaponData& data)
{
	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	UTextManager* text_manager = game_instance->GetTextManager();
	
	reward_data_.gear_type_ = EGearType::Weapon;
	reward_data_.weapon_data_ = data;

	thumbnail_->SetBrushFromTexture(reward_data_.weapon_data_.item_data_.display_data_->thumbnail);
	name_->SetText(text_manager->GetActiveSkillNameText(reward_data_.weapon_data_.item_data_.display_data_->text_key_));
	detail_->SetText(text_manager->GetActiveSkillDetailText(reward_data_.weapon_data_.item_data_.display_data_->text_key_));
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
		check_image_->SetVisibility(ESlateVisibility::Visible);
		equipment_reward_widget_cache_->IncreaseSelectedCounter();
	}
	else
	{
		check_image_->SetVisibility(ESlateVisibility::Hidden);
		equipment_reward_widget_cache_->DecreaseSelectedCounter();
	}
}

bool URewardSelectWidget::GetIsChecked()
{
	return check_box_->IsChecked();
}