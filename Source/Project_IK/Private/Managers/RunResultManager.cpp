/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 03.02.2025
Summary : Source file of a manager that handles UI controls after runs.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Managers/RunResultManager.h"

// Need to call CreateWidget function
#include "Blueprint/UserWidget.h"
#include "UI/ToMainMenuWidget.h"
#include "UI/RunRewardWidget.h"
#include "Managers/EnumCluster.h"

#include "Kismet/GameplayStatics.h"

void URunResultManager::StartRunResultSequence()
{
	if (main_menu_ui_class_)
	{
		
		main_menu_ui_ = CreateWidget<UToMainMenuWidget>(GetWorld(), main_menu_ui_class_);
		if (main_menu_ui_)
		{
			main_menu_ui_->AddToViewport();
			main_menu_ui_->SetVisibility(ESlateVisibility::Hidden);
		}
	}
	if (run_reward_ui_class_)
	{
		run_reward_ui_ = CreateWidget<URunRewardWidget>(GetWorld(), run_reward_ui_class_);
		if (run_reward_ui_)
		{
			run_reward_ui_->AddToViewport();
			run_reward_ui_->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	SwitchUIByState(ERunResultState::ShowingRunRewardUI);
}

void URunResultManager::SwitchUIByState(ERunResultState state)
{
	switch (state)
	{
	case ERunResultState::ShowingRunRewardUI:
		main_menu_ui_->SetVisibility(ESlateVisibility::Hidden);
		run_reward_ui_->SetVisibility(ESlateVisibility::Visible);
		break;
	case ERunResultState::ShowingToMainMenuUI:
		main_menu_ui_->SetVisibility(ESlateVisibility::Visible);
		run_reward_ui_->SetVisibility(ESlateVisibility::Hidden);
		break;
	default:
		verify(false && "SwitchUIByState fall in default state");
		break;
	}
	
	current_state_ = state;
}

FReply URunResultManager::HandleKeyboardAction(const FKeyEvent& InKeyEvent)
{
	switch (current_state_)
	{
	case ERunResultState::ShowingRunRewardUI:
		return run_reward_ui_->NativeOnKeyDown(run_reward_ui_->GetCachedGeometry(), InKeyEvent);
		break;
	case ERunResultState::ShowingToMainMenuUI:
		return main_menu_ui_->NativeOnKeyDown(main_menu_ui_->GetCachedGeometry(), InKeyEvent);
		break;
	default:
		break;
	}
	return FReply::Unhandled();
}
