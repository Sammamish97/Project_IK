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
#include "Structs/WrapperEquipmentData.h"

#include "WorldSettings/StoreLevel/IKStoreHUD.h"

#include "Blueprint/WidgetTree.h"
#include "UI/StoreSlot.h"
#include "UI/ConfirmationWidget.h"
#include "UI/CreditWidget.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "Subsystems/LevelTransitionSubsystem.h"



template<typename ItemType, typename ItemContainer, typename SlotContainer>
inline void UStoreWidget::AddItems(TArray<ItemType> items, ItemContainer& item_container, SlotContainer& slot_container)
{
	for (int32 i = 0; i < items.Num(); i++)
	{
		UStoreSlot* slot = WidgetTree->ConstructWidget<UStoreSlot>(store_widget_class_);
		slot->SetTexture(items[i].item_data_.display_data_->thumbnail);
		slot->SetPrice(GetPriceByRarity(items[i].item_data_.rarity_));
		slot->OnStoreSlotClickedDelegate.AddDynamic(this, &UStoreWidget::OnStoreSlotClicked);
		UHorizontalBoxSlot* box_slot = item_container->AddChildToHorizontalBox(slot);
		if (box_slot)
		{
			box_slot->SetPadding(slot_margin_);
		}
		slot_container.Add(slot);
	}
}


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


	UDataTableManager* manager = game_instance->GetDataTableManager();
	if (store_widget_class_)
	{
		// IKTODO: 웨폰데이터 추가 후 복구
		//weapons_ = manager->GetUniqueWeaponDataRandomly(STOCK);
		//AddItems(weapons_, weapon_slot_container_, weapon_slots_);
		active_skills_ = manager->GetUniqueActiveSkillDataRandomly(STOCK);
		AddItems(active_skills_, active_slot_container_, active_slots_);
		passive_skills_ = manager->GetUniquePassiveSkillDataRandomly(STOCK);
		AddItems(passive_skills_, passive_slot_container_, passive_slots_);
		runes_ = manager->GetUniqueRuneDataRandomly(RUNE_STOCK);
		AddItems(runes_, rune_slot_container_, rune_slots_);
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
		// IKTODO: 웨폰데이터 추가 후 복구
		//if (weapon_slots_[i]->IsChecked())
		//{
		//	total_cost_ += weapon_slots_[i]->GetPrice();
		//}
		if (active_slots_[i]->IsChecked())
		{
			total_cost_ += active_slots_[i]->GetPrice();
		}
		if (passive_slots_[i]->IsChecked())
		{
			total_cost_ += passive_slots_[i]->GetPrice();
		}
	}
	for (int32 i = 0; i < RUNE_STOCK; i++)
	{
		if (rune_slots_[i]->IsChecked())
		{
			total_cost_ += rune_slots_[i]->GetPrice();
		}
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


	FWrapperEquipmentData data;
	for (int32 i = 0; i < STOCK; i++)
	{
		// IKTODO: 웨폰데이터 추가 후 복구
		//if (weapon_slots_[i]->IsChecked())
		//{
		//	data += weapons_[i];
		//}
		if (active_slots_[i]->IsChecked())
		{
			data += active_skills_[i];
		}
		if (passive_slots_[i]->IsChecked())
		{
			data += passive_skills_[i];
		}
	}
	for (int32 i = 0; i < RUNE_STOCK; i++)
	{
		if (rune_slots_[i]->IsChecked())
		{
			data += runes_[i];
		}
	}
	game_instance->GetInventoryManager()->OpenInventoryWidgetReward(data, [&]() 
		{
			GetGameInstance()->GetSubsystem<ULevelTransitionSubsystem>()->OpenMapLevel(GetWorld());
		});

}
