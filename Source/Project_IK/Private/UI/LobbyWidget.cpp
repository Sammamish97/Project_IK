/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.06.2025
Summary : Source file for Lobby widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/LobbyWidget.h"
#include "Components/Button.h"
#include "UI/PerkUnlockWidget.h"
#include "Subsystems/LevelTransitionSubsystem.h"

#include "Kismet/GameplayStatics.h"
#include "Subsystems/PerkProgressSubsystem.h"

#include "WorldSettings/IKGameInstance.h"

void ULobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();
	open_perk_tree_button_->OnClicked.AddDynamic(this, &ULobbyWidget::OnOpenPerkTreeButtonClicked);
	begin_run_button_->OnClicked.AddDynamic(this, &ULobbyWidget::OnBeginRunButtonClicked);
	perk_unlock_widget_->SetVisibility(ESlateVisibility::Hidden);
}

void ULobbyWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void ULobbyWidget::OnOpenPerkTreeButtonClicked()
{
	//PerkTreeWidget열기
	if (is_perk_unlock_widget_opened)
	{
		perk_unlock_widget_->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		perk_unlock_widget_->SetVisibility(ESlateVisibility::Visible);
	}
	is_perk_unlock_widget_opened = !is_perk_unlock_widget_opened;
}

void ULobbyWidget::OnBeginRunButtonClicked()
{
	UIKGameInstance* instance = Cast<UIKGameInstance>(GetGameInstance());
	if (!instance)
	{
		return;
	}

	instance->GetSubsystem<UPerkProgressSubsystem>()->SavePerkDataToDisk();

	instance->LoadRunSaveData();

	//가챠 레벨로 이동.
	ULevelTransitionSubsystem* level_transition_subsystem = GetWorld()->GetGameInstance()->GetSubsystem<ULevelTransitionSubsystem>();
	level_transition_subsystem->OpenLevel(GetWorld(), ELevelState::MapLevel);
}
