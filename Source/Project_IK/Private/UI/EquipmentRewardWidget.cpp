/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 04.08.2025
Summary : Header file for equipment reward widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "UI/EquipmentRewardWidget.h"

#include "Kismet/GameplayStatics.h"
#include "WorldSettings/IKGameInstance.h"
#include "Managers/DataTableManager.h"
#include "Components/Button.h"
#include "WorldSettings/IKHUD.h"
#include "UI/RewardSelectWidget.h"
#include "Components/UniformGridPanel.h"
#include "Managers/InventoryManager.h"

void UEquipmentRewardWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	// IKTODO: number of requested data count may differ by acts.
	const auto& equipments_ = game_instance->GetDataTableManager()->GetUniqueEquipmentDataRandomly(NUM_CANDIDATES);
	
	for (const auto& elem : equipments_.active_skills_)
	{
		auto new_widget = CreateWidget<URewardSelectWidget>(this, reward_widget_class_);
		new_widget->SetRewardData(elem);
		reward_widgets_.Push(new_widget);
	}
	for (const auto& elem : equipments_.passive_skills_)
	{
		auto new_widget = CreateWidget<URewardSelectWidget>(this, reward_widget_class_);
		new_widget->SetRewardData(elem);
		reward_widgets_.Push(new_widget);
	}
	for (const auto& elem : equipments_.weapons_)
	{
		auto new_widget = CreateWidget<URewardSelectWidget>(this, reward_widget_class_);
		new_widget->SetRewardData(elem);
		reward_widgets_.Push(new_widget);
	}
	for (const auto& elem : equipments_.runes_)
	{
		auto new_widget = CreateWidget<URewardSelectWidget>(this, reward_widget_class_);
		new_widget->SetRewardData(elem);
		reward_widgets_.Push(new_widget);
	}
	for (const auto& elem : equipments_.support_skills_)
	{
		auto new_widget = CreateWidget<URewardSelectWidget>(this, reward_widget_class_);
		new_widget->SetRewardData(elem);
		reward_widgets_.Push(new_widget);
	}

	for (const auto& elem : reward_widgets_)
	{
		elem->SetEquipmentWidgetCache(this);
		reward_container_->AddChildToHorizontalBox(elem);
	}

	confirm_button_->OnClicked.AddDynamic(this, &UEquipmentRewardWidget::OnConfirmButtonClicked);
}

void UEquipmentRewardWidget::NativeDestruct()
{
	Super::NativeDestruct();

	reward_widgets_.Empty();
	confirm_button_->OnClicked.Clear();
}

void UEquipmentRewardWidget::IncreaseSelectedCounter()
{
	selected_amount = FMath::Min(selected_amount + 1, MAX_CHOICE);
	//만약 선택 한계에 도달했다면, 선택되지 못한 widget들을 disable 시킨다.
	if (selected_amount >= MAX_CHOICE)
	{
		for (auto& elem : reward_widgets_)
		{
			if (elem->GetIsChecked() == false)
			{
				elem->SetIsEnabled(false);
			}
		}
	}
}

void UEquipmentRewardWidget::DecreaseSelectedCounter()
{
	selected_amount = FMath::Max(selected_amount - 1, 0);
	//모든 widget을 enable 시킨다.
	for (auto& elem : reward_widgets_)
	{
		elem->SetIsEnabled(true);
	}	
}

bool UEquipmentRewardWidget::AbleToSelectMoreReward()
{
	return selected_amount < MAX_CHOICE;
}

void UEquipmentRewardWidget::OnConfirmButtonClicked()
{
	FWrapperEquipmentData selected_reward_data;
	AIKHUD* hud = Cast<AIKHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
	if (hud)
	{
		for (const auto& elem : reward_widgets_)
		{
			if (elem->GetIsChecked())
			{
				const auto& reward_data = elem->GetRewardData();
				switch (reward_data.gear_type_)
				{
				case EGearType::Weapon:
					selected_reward_data.weapons_.Push(reward_data.weapon_data_);
					break;
				case EGearType::ActiveSkill:
					selected_reward_data.active_skills_.Push(reward_data.active_skill_data_);
					break;
				case EGearType::PassiveSkill:
					selected_reward_data.passive_skills_.Push(reward_data.passive_skill_data_);
					break;
				case EGearType::Rune:
					selected_reward_data.runes_.Push(reward_data.rune_data_);
					break;
				case EGearType::SupportSkill:
					selected_reward_data.support_skills_.Push(reward_data.support_skill_data_);
					break;
				default:
					break;
					//IKTODO: 예외처리
				}
			}
		}

		UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		game_instance->GetInventoryManager()->OpenInventoryWidgetReward(selected_reward_data);
		hud->SwitchUIByState(ECombatEndState::ShowingInventoryUI);
	}
}
