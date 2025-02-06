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
#include "Managers/ItemDataManager.h"
#include "Managers/DronePluginManager.h"
#include "Abilities/ItemInventory.h"
#include "Managers/HeroInventoryManager.h"

#include "WorldSettings/StoreLevel/IKStoreHUD.h"

#include "Blueprint/WidgetTree.h"
#include "UI/StoreSlot.h"
#include "UI/ConfirmationWidget.h"
#include "UI/CreditWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

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
	const UItemDataManager* item_data_manager = game_instance->GetItemDataManager();
	const UDronePluginManager* drone_plugin_manager = game_instance->GetDronePluginManager();

	if (!item_data_manager || !drone_plugin_manager)
	{
		return;
	}

	items_ = item_data_manager->GetUniqueItemDataRandomly(STOCK);
	dps_ = drone_plugin_manager->GetUniqueDPDataRandomly(STOCK);
	item_slots_.Empty();
	dp_slots_.Empty();
	
	credits_ = game_instance->GetInventoryManager()->GetCredits();


	if (store_widget_class_)
	{
		for (int32 i = 0; i < STOCK; i++)
		{
			UStoreSlot* slot = WidgetTree->ConstructWidget<UStoreSlot>(store_widget_class_);
			slot->SetTexture(items_[i]->item_icon_);
			slot->SetPrice(GetPriceByRarity(items_[i]->rarity_));
			slot->OnStoreSlotClickedDelegate.AddDynamic(this, &UStoreWidget::OnStoreSlotClicked);
			UHorizontalBoxSlot* box_slot = item_container_->AddChildToHorizontalBox(slot);
			if (box_slot)
			{
				box_slot->SetPadding(FMargin(120.f, 0.f));
			}
			item_slots_.Add(slot);
		}

		for (int32 i = 0; i < STOCK; i++)
		{
			UStoreSlot* slot = WidgetTree->ConstructWidget<UStoreSlot>(store_widget_class_);
			slot->SetTexture(dps_[i].dp_icon_);
			slot->SetPrice(GetPriceByRarity(dps_[i].rarity_));
			slot->OnStoreSlotClickedDelegate.AddDynamic(this, &UStoreWidget::OnStoreSlotClicked);
			UHorizontalBoxSlot* box_slot = dp_container_->AddChildToHorizontalBox(slot);
			if (box_slot)
			{
				box_slot->SetPadding(FMargin(120.f, 0.f));
			}
			dp_slots_.Add(slot);
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

	item_slots_.Empty();
	dp_slots_.Empty();
}

void UStoreWidget::OnPayButtonClicked()
{
	if (!confirmation_widget_)
	{
		return;
	}

	if (total_cost_ <= 0)
	{
		confirmation_widget_->SetText(FText::FromString("Are you sure you want to leave? This action cannot be undone."));
		confirmation_widget_->AddToViewport();
	}
	else if (total_cost_ <= credits_)
	{
		// Are you sure you want to purchase this item? This action cannot be undone.
		FText confirm_text = FText::Format(NSLOCTEXT("NameSpace", "StoreConfirmationMessage", "Do you want to complete your purchase of items for {0}?"), FText::AsNumber(total_cost_));
		confirmation_widget_->SetText(confirm_text);
		confirmation_widget_->AddToViewport();
	}
	else
	{
		casher_text_->SetText(FText::FromString("Not enough money, huh? Try picking something that actually fits your purse."));
	}
}

void UStoreWidget::OnStoreSlotClicked()
{
	total_cost_ = 0;
	for (int32 i = 0; i < STOCK; i++)
	{
		if (item_slots_[i]->IsChecked())
		{
			total_cost_ += item_slots_[i]->GetPrice();
		}
		if (dp_slots_[i]->IsChecked())
		{
			total_cost_ += dp_slots_[i]->GetPrice();
		}
	}

	total_cost_text_->SetText(FText::FromString(FString::FromInt(total_cost_)));

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
	case ERarity::S:
		return 100;
		break;
	case ERarity::A:
		return 75;
		break;
	case ERarity::B:
	default:
		return 50;
		break;
	}
}

void UStoreWidget::GoToNextLevel()
{
	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	// Save purchased items and dps
	UHeroInventoryManager* inventory_manager = game_instance->GetInventoryManager();
	inventory_manager->SetCredits(credits_ - total_cost_);
	credit_widget_->UpdateCreditText();
	

	TArray<FItemData*> selected_items;
	TArray<FDPData> selected_dps;
	for (int32 i = 0; i < STOCK; i++)
	{
		if (item_slots_[i]->IsChecked())
		{
			selected_items.Add(items_[i]);
		}
		if (dp_slots_[i]->IsChecked())
		{
			selected_dps.Add(dps_[i]);
		}
	}
	//TODO: 사라진 DP에 대응하기 위해 주석 처리.
	// for (int32 i = 0; i < selected_dps.Num(); i++)
	// {
	// 	inventory_manager->AddDP(selected_dps[i].dp_type_);
	// }
	game_instance->GetItemInventory()->AddItems(selected_items, [this]() {
		// Update HUD status
		AIKStoreHUD* hud = Cast<AIKStoreHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
		if (hud)
		{
			hud->DisplayMapWidget();
		}
		}
	);

	// Pop up map widget to go to next levels.
}
