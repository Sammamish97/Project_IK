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

#include "Blueprint/WidgetTree.h"
#include "UI/StoreSlot.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

bool UStoreWidget::Initialize()
{
	Super::Initialize();
	total_cost_ = 0;
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

	pay_button_->OnClicked.AddDynamic(this, &UStoreWidget::OnPayButtonClicked);
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
