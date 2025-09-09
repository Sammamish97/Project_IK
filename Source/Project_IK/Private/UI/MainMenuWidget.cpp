/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.06.2025
Summary : Source file for main menu widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/MainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Subsystems/LevelTransitionSubsystem.h"

#include "UI/Settings/SettingWidget.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	new_game_button_->OnClicked.AddDynamic(this, &UMainMenuWidget::OnNewGameButtonClicked);
	continue_button_->OnClicked.AddDynamic(this, &UMainMenuWidget::OnContinueButtonClicked);
	setting_button_->OnClicked.AddDynamic(this, &UMainMenuWidget::OnSettingButtonClicked);
	exit_button_->OnClicked.AddDynamic(this, &UMainMenuWidget::OnExitButtonClicked);
}

void UMainMenuWidget::NativeDestruct()
{
	new_game_button_->OnClicked.Clear();
	continue_button_->OnClicked.Clear();
	setting_button_->OnClicked.Clear();
	exit_button_->OnClicked.Clear();

	Super::NativeDestruct();
}

void UMainMenuWidget::OnNewGameButtonClicked()
{
	//세이브 데이터 초기화
	//네러티브 레벨로 이동
}

void UMainMenuWidget::OnContinueButtonClicked()
{
	//세이브 데이터 로드
	//세이브 파일에 따라서 전투 준비/지도 레벨로 이동
	//만약 세이브 파일이 없다면 disable되어 클릭할 수 없어야 함.
	ULevelTransitionSubsystem* level_transition_subsystem = GetWorld()->GetGameInstance()->GetSubsystem<ULevelTransitionSubsystem>();
	level_transition_subsystem->OpenLevel(GetWorld(), ELevelState::LobbyLevel);
}

void UMainMenuWidget::OnSettingButtonClicked()
{
	UUserWidget* setting_ui = CreateWidget<USettingWidget>(GetWorld(), setting_ui_class_);

	if (setting_ui)
	{
		setting_ui->AddToViewport();
	}
}

void UMainMenuWidget::OnExitButtonClicked()
{
	//게임 종료
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, false);
}
