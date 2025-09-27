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
#include "Components/TextBlock.h"
#include "UI/PerkUnlockWidget.h"
#include "Subsystems/LevelTransitionSubsystem.h"

#include "Kismet/GameplayStatics.h"
#include "Subsystems/PerkProgressSubsystem.h"
#include "Subsystems/PerkModifierSubsystem.h"
#include "UI/PerkTrees/PerkHUDWidget.h"

#include "WorldSettings/IKGameInstance.h"
#include "SaveGame/SaveRunProgress.h"

void ULobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	auto text_manager_cache = game_instance->GetTextManager();
	
	open_perk_tree_button_->OnClicked.AddDynamic(this, &ULobbyWidget::OnOpenPerkTreeButtonClicked);
	open_perk_tree_text_->SetText(text_manager_cache->GetButtonText(EButtonType::OpenPerkTree));

	begin_run_button_->OnClicked.AddDynamic(this, &ULobbyWidget::OnBeginRunButtonClicked);
	begin_run_text_->SetText(text_manager_cache->GetButtonText(EButtonType::BeginRun));
	
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
	UIKGameInstance* instance = Cast<UIKGameInstance>(GetGameInstance());
	if (!instance)
	{
		return;
	}

	instance->LoadRunSaveData();

	ULevelTransitionSubsystem* level_transition_subsystem = GetWorld()->GetGameInstance()->GetSubsystem<ULevelTransitionSubsystem>();
	
	// Guides players to Gotcha level if and only if...
		// Available an amount of gotcha pulls.
		// Player is going to begin a new run.
	int32 num_max_pull = GetGameInstance()->GetSubsystem<UPerkModifierSubsystem>()->GetNumMaxPull();
	if (num_max_pull > 0 && 
		USaveRunProgress::StaticClass()->GetDefaultObject<USaveRunProgress>()->DoesSaveGameExist() == false)
	{
		level_transition_subsystem->OpenLevel(GetWorld(), ELevelState::GotchaLevel);
	}
	else
	{
		level_transition_subsystem->OpenLevel(GetWorld(), ELevelState::MapLevel);
	}

}

UPerkHUDWidget* ULobbyWidget::GetPerkTreeWidget()
{
	return perk_tree_hud_widget_;
}
