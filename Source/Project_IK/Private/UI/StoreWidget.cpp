/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 01.15.2025
Summary : Source file for main Widget in StoreLevel.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/StoreWidget.h"

#include "Kismet/GameplayStatics.h"
#include "WorldSettings/IKGameInstance.h"
#include "Managers/InventoryManager.h"
#include "Managers/DataTableManager.h"

#include "WorldSettings/StoreLevel/IKStoreHUD.h"

#include "Blueprint/WidgetTree.h"
#include "UI/StoreSlot.h"
#include "UI/ConfirmationWidget.h"
#include "UI/CreditWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Managers/DataTableManager.h"

#include "Subsystems/LevelTransitionSubsystem.h"

bool UStoreWidget::Initialize()
{
	Super::Initialize();
	total_cost_ = 0;
	credits_ = 0;
	return true;
}

void UStoreWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!game_instance)
	{
		return;
	}

	credits_ = game_instance->GetInventoryManager()->GetCredits();
	
	if (store_widget_class_)
	{
		for (int32 i = 0; i < STOCK; i++)
		{
			// Fill here to list items
		}
	}

	if (confirmation_widget_class_)
	{
		confirmation_widget_ = WidgetTree->ConstructWidget<UConfirmationWidget>(confirmation_widget_class_);
		confirmation_widget_->OnConfirmation.AddDynamic(this, &UStoreWidget::GoToNextLevel);
	}

	pay_button_->OnClicked.AddDynamic(this, &UStoreWidget::OnPayButtonClicked);
	pay_button_->SetStyle(leave_style_);
}

void UStoreWidget::NativeDestruct()
{
	Super::NativeDestruct();

	pay_button_->OnClicked.Clear();

	if (confirmation_widget_->OnConfirmation.IsBound())
	{
		confirmation_widget_->OnConfirmation.Clear();
	}
}

void UStoreWidget::OnPayButtonClicked()
{
	if (!confirmation_widget_)
	{
		return;
	}

	if (total_cost_ <= 0)
	{
		confirmation_widget_->SetText(NSLOCTEXT("UI", "StoreLeave", "Are you sure you want to leave? This action cannot be undone."));
		confirmation_widget_->AddToViewport();
	}
	else if (total_cost_ <= credits_)
	{
		// Are you sure you want to purchase this item? This action cannot be undone.
		FText confirm_text = FText::Format(NSLOCTEXT("UI", "StorePurchase", "Do you want to complete your purchase of items for {0}?"), FText::AsNumber(total_cost_));
		confirmation_widget_->SetText(confirm_text);
		confirmation_widget_->AddToViewport();
	}
	else
	{
		casher_text_->SetText(NSLOCTEXT("UI", "StoreNeedMoney", "Not enough money, huh? Try picking something that actually fits your purse."));
	}
}

void UStoreWidget::OnStoreSlotClicked()
{
	total_cost_ = 0;
	for (int32 i = 0; i < STOCK; i++)
	{
		// Mark an item that user mouse is hovering
	}

	total_cost_text_->SetText(FText::AsNumber(total_cost_));

	// Update button style
	if (total_cost_ <= 0)
	{
		pay_button_->SetStyle(leave_style_);
	}
	else
	{
		pay_button_->SetStyle(purchase_style_);
	}
}

int32 UStoreWidget::GetPriceByRarity(ERarity rarity)
{
	switch (rarity)
	{
	case ERarity::Legendary:
		return 100;
		break;
	case ERarity::Rare:
		return 75;
		break;
	case ERarity::Common:
	default:
		return 50;
		break;
	}
}

void UStoreWidget::GoToNextLevel()
{
	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	// Save purchased items and dps
	UInventoryManager* inventory_manager = game_instance->GetInventoryManager();
	inventory_manager->SetCredits(credits_ - total_cost_);
	credit_widget_->UpdateCreditText();
	

	for (int32 i = 0; i < STOCK; i++)
	{
		// Add purchased items to inventory
	}

	game_instance->GetSubsystem<ULevelTransitionSubsystem>()->OpenMapLevel(GetWorld());
}
