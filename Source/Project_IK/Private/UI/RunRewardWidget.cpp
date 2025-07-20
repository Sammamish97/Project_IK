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

#include "UI/IKMaps.h"

void URunRewardWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (game_instance)
	{
		UIKMaps* maps = game_instance->GetMapPtr();
		if (maps)
		{
			TArray<FIntPoint> path = maps->GetPlayerVisitedPath();

			perk_points_reward_ = path.Num();

			for (FIntPoint node_index : path)
			{
				FMapNode node = maps->GetNode(node_index.X, node_index.Y);

				// @@ TODO: Need to add handle when the nodetype is elite enemy.
				// @@ TODO: Need to concern result of boss battle.
						// Since UIKMaps::SetPlayerGridPosition record boss node has been visited whether combat result,
						// perk_points_reward_ always provided whether boss defeated or not.
				switch (node.type)
				{
				case NodeType::Enemy:
					++perk_points_reward_;
					break;
				case NodeType::Boss:
					perk_points_reward_ += 2;
					break;
				default:
					break;
				}
			}
		}
	}


	perk_points_text_->SetText(FText::AsNumber(perk_points_reward_));
}

void URunRewardWidget::NativeDestruct()
{
	Super::NativeDestruct();

	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (game_instance)
	{
		UInventoryManager* inventory = game_instance->GetInventoryManager();
		inventory->SetPerkPoints(inventory->GetPerkPoints() + perk_points_reward_);
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
