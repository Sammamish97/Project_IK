/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 11.20.2024
Summary : Header file of a manager that handles UI controls after combats.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Managers/CombatLevelResultManager.h"
#include "Managers/EnumCluster.h"

#include "Kismet/GameplayStatics.h"
#include "Managers/EnumCluster.h"
#include "Subsystems/LevelTransitionSubsystem.h"

#include "UI/CombatResultUI.h"
#include "UI/EquipmentRewardWidget.h"
#include "UI/ToMainMenuWidget.h"


void UCombatLevelResultManager::InitializeUI()
{
	UWorld* world = GetWorld();

	if (combat_result_widget_class_)
	{
		combat_result_widget_ = CreateWidget<UCombatResultUI>(world, combat_result_widget_class_);
		if (combat_result_widget_)
		{
			combat_result_widget_->AddToViewport();
			combat_result_widget_->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (equipment_reward_widget_class_)
	{
		equipment_reward_widget_ = CreateWidget<UEquipmentRewardWidget>(world, equipment_reward_widget_class_);
		if (equipment_reward_widget_)
		{
			equipment_reward_widget_->AddToViewport();
			equipment_reward_widget_->SetVisibility(ESlateVisibility::Hidden);
		}
	}


	if (main_menu_ui_class_)
	{

		main_menu_ui_ = CreateWidget<UToMainMenuWidget>(GetWorld(), main_menu_ui_class_);
		if (main_menu_ui_)
		{
			main_menu_ui_->AddToViewport();
			main_menu_ui_->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UCombatLevelResultManager::DisplayCombatResult(const TMap<EHeroType, float>& damage_map)
{
	if (combat_result_widget_)
	{
		combat_result_widget_->SetVisibility(ESlateVisibility::Visible);
		combat_result_widget_->UpdateResults(damage_map);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Combat result widget is NOT valid!"));
	}
}

void UCombatLevelResultManager::SwitchUIByState(ECombatEndState state)
{
	if (!combat_result_widget_)
	{
		UE_LOG(LogTemp, Error, TEXT("Any of the widgets serialized in LevelEndUIManager is NOT valid!"));
		return;
	}

	switch (state)
	{
	case ECombatEndState::ShowingCombatResultUI:
		combat_result_widget_->SetVisibility(ESlateVisibility::Visible);
		equipment_reward_widget_->SetVisibility(ESlateVisibility::Hidden);
		main_menu_ui_->SetVisibility(ESlateVisibility::Hidden);
		break;
	case ECombatEndState::ShowingEquipmentRewardUI:
		combat_result_widget_->SetVisibility(ESlateVisibility::Hidden);
		equipment_reward_widget_->SetVisibility(ESlateVisibility::Visible);
		main_menu_ui_->SetVisibility(ESlateVisibility::Hidden);
			break;
	case ECombatEndState::ShowingInventoryUI:
		equipment_reward_widget_->SetVisibility(ESlateVisibility::Hidden);
		break;

	case ECombatEndState::ShowingMapUI:
		UGameplayStatics::GetGameInstance(GetWorld())->GetSubsystem<ULevelTransitionSubsystem>()->OpenMapLevel(GetWorld());
		break;
	case ECombatEndState::ShowingToMainmenu:
		combat_result_widget_->SetVisibility(ESlateVisibility::Hidden);
		equipment_reward_widget_->SetVisibility(ESlateVisibility::Hidden);
		main_menu_ui_->SetVisibility(ESlateVisibility::Visible);
		break;
	default:
		break;
	}
}
