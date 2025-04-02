/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 03.31.2025
Summary : Source file for Run reward widget.
					It distributes reward for completing a run.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/RunRewardWidget.h"

#include "Managers/EnumCluster.h"
#include "WorldSettings/RunResultLevel/IKRunResultHUD.h"

#include "Components/TextBlock.h"

#include "Kismet/GameplayStatics.h"
#include "WorldSettings/IKGameInstance.h"
#include "Managers/InventoryManager.h"

void URunRewardWidget::NativeConstruct()
{
	Super::NativeConstruct();


	perk_points_text_->SetText(FText::AsNumber(perk_points_reward_));
	ticket_text_->SetText(FText::AsNumber(tickets_reward_));
}

void URunRewardWidget::NativeDestruct()
{
	Super::NativeDestruct();

	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (game_instance)
	{
		UInventoryManager* inventory = game_instance->GetInventoryManager();
		inventory->SetPerkPoints(inventory->GetPerkPoints() + perk_points_reward_);
		inventory->SetTickets(inventory->GetTickets() + tickets_reward_);
	}
}

FReply URunRewardWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	APlayerController* pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (pc)
	{
		AIKRunResultHUD* hud = Cast<AIKRunResultHUD>(pc->GetHUD());
		if (hud)
		{
			hud->SwitchUIByState(ERunResultState::ShowingToMainMenuUI);
		}
	}
	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

FReply URunRewardWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	// Left this function for future.
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}
