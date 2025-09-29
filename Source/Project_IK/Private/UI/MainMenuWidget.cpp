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
#include "Components/TextBlock.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Subsystems/LevelTransitionSubsystem.h"

#include "UI/Settings/SettingWidget.h"

#include "WorldSettings/IKGameInstance.h"
#include "UI/Map/IKMaps.h"

#include "SaveGame/SavePerkProgress.h"
#include "SaveGame/SaveRunProgress.h"
#include "Subsystems/PerkProgressSubsystem.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	new_game_button_->OnClicked.AddDynamic(this, &UMainMenuWidget::OnNewGameButtonClicked);

	if (IsContinuable())
	{
		continue_button_->OnClicked.AddDynamic(this, &UMainMenuWidget::OnContinueButtonClicked);
	}
	else
	{
		continue_button_->SetIsEnabled(false);
	}
	option_button_->OnClicked.AddDynamic(this, &UMainMenuWidget::OnSettingButtonClicked);
	quit_button_->OnClicked.AddDynamic(this, &UMainMenuWidget::OnExitButtonClicked);

	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	UTextManager* text_manager = game_instance->GetTextManager();
	
	new_game_text_->SetText(text_manager->GetButtonText(EButtonType::NewGame));
	continue_text_->SetText(text_manager->GetButtonText(EButtonType::Continue));
	option_text_->SetText(text_manager->GetButtonText(EButtonType::Option));
	quit_text_->SetText(text_manager->GetButtonText(EButtonType::Quit));
}

void UMainMenuWidget::NativeDestruct()
{
	new_game_button_->OnClicked.Clear();
	continue_button_->OnClicked.Clear();
	option_button_->OnClicked.Clear();
	quit_button_->OnClicked.Clear();

	Super::NativeDestruct();
}

void UMainMenuWidget::OnNewGameButtonClicked()
{
	//세이브 데이터 초기화
	USavePerkProgress::StaticClass()->GetDefaultObject<USavePerkProgress>()->DeleteSaveFile();
	USaveRunProgress::StaticClass()->GetDefaultObject<USaveRunProgress>()->DeleteSaveFile();



	//네러티브 레벨로 이동

	UIKGameInstance* instance = Cast<UIKGameInstance>(GetGameInstance());


	if (instance)
	{
		// Clear memory data that loaded at the game beginning.
		instance->ClearRunData();

		// Generate map data
		UIKMaps* map = instance->GetMapPtr();
		map->GenerateMaps(10, 5);
		instance->GetSubsystem<UPerkProgressSubsystem>()->Clear();
	}
	ULevelTransitionSubsystem* level_transition_subsystem = GetWorld()->GetGameInstance()->GetSubsystem<ULevelTransitionSubsystem>();
	level_transition_subsystem->OpenLevel(GetWorld(), ELevelState::Opening);
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

bool UMainMenuWidget::IsContinuable()
{
	return USavePerkProgress::StaticClass()->GetDefaultObject<USavePerkProgress>()->DoesSaveGameExist() ||
		USaveRunProgress::StaticClass()->GetDefaultObject<USaveRunProgress>()->DoesSaveGameExist();
}
