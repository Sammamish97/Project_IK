/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.06.2025
Summary : Header file for inventory manager.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Managers/InventoryManager.h"
#include "UI/Inventory/InventoryWidget.h"
#include "Subsystems/PerkModifierSubsystem.h"

void UInventoryManager::OpenInventoryWidgetReward(const FWrapperEquipmentData& rewards, TFunction<void()> OnConfirm)
{
	if(inventory_widget_class_)
	{
		inventory_widget_ = CreateWidget<UInventoryWidget>(GetWorld(), inventory_widget_class_);
		if(inventory_widget_)
		{
			inventory_widget_->LoadSelectedRewards(rewards);
			UPerkModifierSubsystem* perk_modifier = GetWorld()->GetGameInstance()->GetSubsystem<UPerkModifierSubsystem>();
			inventory_widget_->InitInventoryWidget(perk_modifier->GetInventoryPassiveSkillUnlockedSlots(), false);
			inventory_widget_->SetOnConfirm(OnConfirm);
			inventory_widget_->AddToViewport();
			inventory_widget_->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void UInventoryManager::OpenReadOnlyInventoryWidget()
{
	if(inventory_widget_class_)
	{
		inventory_widget_ = CreateWidget<UInventoryWidget>(GetWorld(), inventory_widget_class_);
		if(inventory_widget_)
		{
			UPerkModifierSubsystem* perk_modifier = GetWorld()->GetGameInstance()->GetSubsystem<UPerkModifierSubsystem>();
			inventory_widget_->InitInventoryWidget(perk_modifier->GetInventoryPassiveSkillUnlockedSlots(), true);
			inventory_widget_->AddToViewport();
			inventory_widget_->SetVisibility(ESlateVisibility::Visible);
		}
	}
}

void UInventoryManager::SetCredits(int32 credits)
{
	credits_ = credits;
}

void UInventoryManager::AddCredits(int32 currency)
{
	credits_ += currency;
}

int32 UInventoryManager::GetCredits() const
{
	return credits_;
}