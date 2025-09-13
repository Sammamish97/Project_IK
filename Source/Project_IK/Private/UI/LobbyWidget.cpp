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
#include "SaveGame/SavePerkProgress.h"
#include "Subsystems/PerkProgressSubsystem.h"
#include "UI/PerkTrees/PerkHUDWidget.h"

void ULobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();
	open_perk_tree_button_->OnClicked.AddDynamic(this, &ULobbyWidget::OnOpenPerkTreeButtonClicked);
	begin_run_button_->OnClicked.AddDynamic(this, &ULobbyWidget::OnBeginRunButtonClicked);
	perk_tree_hud_widget_->SetVisibility(ESlateVisibility::Hidden);
}

void ULobbyWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void ULobbyWidget::OnOpenPerkTreeButtonClicked()
{
	perk_tree_hud_widget_->SetVisibility(ESlateVisibility::Visible);
}

void ULobbyWidget::OnBeginRunButtonClicked()
{
	SavePerkData();

	//가챠 레벨로 이동.
	ULevelTransitionSubsystem* level_transition_subsystem = GetWorld()->GetGameInstance()->GetSubsystem<ULevelTransitionSubsystem>();
	level_transition_subsystem->OpenLevel(GetWorld(), ELevelState::MapLevel);
}

void ULobbyWidget::SavePerkData()
{
	USavePerkProgress* save_game_instance = Cast<USavePerkProgress>(UGameplayStatics::CreateSaveGameObject(USavePerkProgress::StaticClass()));

	UPerkProgressSubsystem* subsystem = GetGameInstance()->GetSubsystem<UPerkProgressSubsystem>();
	if (save_game_instance && subsystem)
	{
		save_game_instance->perk_node_map_ = subsystem->LoadAllPerkDetails();

		save_game_instance->perk_points_ = subsystem->LoadPerkPoint();
	}

	UGameplayStatics::SaveGameToSlot(save_game_instance, save_game_instance->GetSaveSlotName(), 0);
}

UPerkHUDWidget* ULobbyWidget::GetPerkTreeWidget()
{
	return perk_tree_hud_widget_;
}
