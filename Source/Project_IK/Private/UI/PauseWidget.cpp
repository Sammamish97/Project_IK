/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.07.2025
Summary : Source file for pause widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/PauseWidget.h"
#include "Components/Button.h"
#include "Subsystems/LevelTransitionSubsystem.h"
#include "WorldSettings/IKPlayerController.h"

void UPauseWidget::NativeConstruct()
{
	Super::NativeConstruct();
	resume_button_->OnClicked.AddDynamic(this, &UPauseWidget::OnResumeButtonClicked);
	return_to_main_menu_button_->OnClicked.AddDynamic(this, &UPauseWidget::OnReturnToMainMenuButtonClicked);
}

void UPauseWidget::NativeDestruct()
{
	Super::NativeDestruct();
	resume_button_->OnClicked.Clear();
	return_to_main_menu_button_->OnClicked.Clear();
}

void UPauseWidget::OnResumeButtonClicked()
{
	auto pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	Cast<AIKPlayerController>(pc)->TogglePause();
}

void UPauseWidget::OnReturnToMainMenuButtonClicked()
{
	ULevelTransitionSubsystem* level_transition_subsystem = GetWorld()->GetGameInstance()->GetSubsystem<ULevelTransitionSubsystem>();
	level_transition_subsystem->OpenLevel(GetWorld(), ELevelState::MainMenuLevel);
}