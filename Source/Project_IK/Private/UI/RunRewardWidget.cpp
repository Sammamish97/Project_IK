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

#include "UI/Map/IKMaps.h"
#include "Subsystems/PerkProgressSubsystem.h"
#include "SaveGame/SaveRunProgress.h"

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
					++combat_num_;
					break;
				case NodeType::Merchant:
					++store_num_;
					break;
				case NodeType::Event:
					++event_num_;
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


	combat_num_text_->SetText(FText::AsNumber(combat_num_));
	event_num_text_->SetText(FText::AsNumber(event_num_));
	store_num_text_->SetText(FText::AsNumber(store_num_));
	perk_points_text_->SetText(FText::AsNumber(perk_points_reward_));
}

void URunRewardWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

FReply URunRewardWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	GrantsPerkPoints();

	if (on_confirm_)
	{
		on_confirm_();
	}
	else
	{
		RemoveFromParent();
	}

	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

FReply URunRewardWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	GrantsPerkPoints();

	if (on_confirm_)
	{
		on_confirm_();
	}
	else
	{
		RemoveFromParent();
	}

	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void URunRewardWidget::SetOnConfirm(TFunction<void()> on_confirm)
{
	on_confirm_ = on_confirm;
}


void URunRewardWidget::GrantsPerkPoints()
{
	if (has_granted_)
	{
		return;
	}
	else
	{
		UPerkProgressSubsystem* subsystem = GetGameInstance()->GetSubsystem<UPerkProgressSubsystem>();
		subsystem->SavePerkPoint(subsystem->LoadPerkPoint() + perk_points_reward_);
		subsystem->SavePerkDataToDisk();

		has_granted_ = true;
	}
}