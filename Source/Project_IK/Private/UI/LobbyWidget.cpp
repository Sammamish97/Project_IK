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
#include "UI/PerkTrees/PerkHUDWidget.h"

#include "WorldSettings/IKGameInstance.h"

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
UPerkHUDWidget* ULobbyWidget::GetPerkTreeWidget()
{
	return perk_tree_hud_widget_;
}
