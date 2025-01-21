/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 01.08.2025
Summary : Source file of widget that choose whether keep the item or discard.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/ItemKeepOrDiscardWidget.h"

#include "Blueprint/WidgetTree.h"
#include "UI/CheckboxButtonWidget.h"
#include "Components/GridPanel.h"
#include "Components/GridSlot.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

#include "Kismet/GameplayStatics.h"
#include "WorldSettings/IKGameInstance.h"
#include "Managers/TextureManager.h"
#include "Managers/ItemDataManager.h"
#include "Abilities/ItemInventory.h"

bool UItemKeepOrDiscardWidget::Initialize()
{
	Super::Initialize();
	candidates_items_.Empty();
	candidates_items_widgets_.Empty();
	inventory_items_.Empty();
	inventory_items_widgets_.Empty();

	checked_items_num_ = 0;
	return true;
}

void UItemKeepOrDiscardWidget::UpdateItems(TArray<FItemData*> inventory_items, TArray<FItemData*> candidates_items)
{
	const int32 inventory_item_capacity = FMath::Min(UItemInventory::INVENTORY_CAPACITY, inventory_items.Num());
	for (int32 i = 0; i < inventory_item_capacity; i++)
	{
		AddItemCheckboxInventory(inventory_items[i]);
	}
	checked_items_num_ = inventory_item_capacity;
	AddItemCheckboxCandidates(candidates_items);
}

void UItemKeepOrDiscardWidget::NativeConstruct()
{
	Super::NativeConstruct();

	confirm_button_->OnClicked.AddDynamic(this, &UItemKeepOrDiscardWidget::OnConfirmButtonClicked);

	for (UCheckboxButtonWidget* widget : candidates_items_widgets_)
	{
		widget->OnCheckboxButtonClickedDelegate.AddDynamic(this, &UItemKeepOrDiscardWidget::OnCheckboxButtonClicked);
	}
	for (UCheckboxButtonWidget* widget : inventory_items_widgets_)
	{
		widget->OnCheckboxButtonClickedDelegate.AddDynamic(this, &UItemKeepOrDiscardWidget::OnCheckboxButtonClicked);
	}
}

void UItemKeepOrDiscardWidget::NativeDestruct()
{
	OnConfirmed.Clear();
}

void UItemKeepOrDiscardWidget::OnConfirmButtonClicked()
{
	TArray<FItemData> selected_items;

	for (UCheckboxButtonWidget* widget : inventory_items_widgets_)
	{
		if (widget->IsChecked())
		{
			selected_items.Add(*widget->GetItem());
		}
	}
	for (UCheckboxButtonWidget* widget : candidates_items_widgets_)
	{
		if (widget->IsChecked())
		{
			selected_items.Add(*widget->GetItem());
		}
	}

	if (OnConfirmed.IsBound())
	{
		OnConfirmed.Broadcast(selected_items);
	}

	if (IsInViewport())
	{
		RemoveFromParent();
	}
}

void UItemKeepOrDiscardWidget::OnCheckboxButtonClicked()
{
	for (UCheckboxButtonWidget* widget : candidates_items_widgets_)
	{
		// Finish callbackfunction if toggled.
		if (ToggleCheckboxButton(widget))
		{
			return;
		}
	}
	for (UCheckboxButtonWidget* widget : inventory_items_widgets_)
	{
		if (ToggleCheckboxButton(widget))
		{
			return;
		}
	}
}

bool UItemKeepOrDiscardWidget::ToggleCheckboxButton(UCheckboxButtonWidget* widget)
{
	if (widget->IsHovered())
	{
		item_text_->SetText(FText::FromString(widget->GetItem()->item_description_));
		if (widget->IsChecked())
		{
			if (checked_items_num_ < UItemInventory::INVENTORY_CAPACITY)
			{
				++checked_items_num_;
			}
			else
			{
				// When user tries selecting items more than inventory capacity,
				// Toggle again to make it not pressed. 
				widget->ToggleChecked();
			}
		}
		else
		{
			--checked_items_num_;
		}
		return true;
	}
	return false;
}

void UItemKeepOrDiscardWidget::AddItemCheckboxInventory(FItemData* item_data)
{
	UCheckboxButtonWidget* cb = WidgetTree->ConstructWidget<UCheckboxButtonWidget>(check_box_button_class_);
	if (cb)
	{
		UHorizontalBoxSlot* cb_slot = inventory_item_container_->AddChildToHorizontalBox(cb);
		if (cb_slot)
		{
			cb_slot->SetPadding(FMargin(64.f, 0.f));
		}
		cb->SetItem(item_data);
		cb->ToggleChecked();

		inventory_items_widgets_.Add(cb);
		inventory_items_.Add(item_data);
	}
}

void UItemKeepOrDiscardWidget::AddItemCheckboxCandidates(TArray<FItemData*> candidates_items)
{
	const int32 horizontal_box_num = (candidates_items.Num() / MAX_ROW) + 1;
	for (int32 i = 0; i < horizontal_box_num; i++)
	{
		UHorizontalBox* horizontal_box = WidgetTree->ConstructWidget<UHorizontalBox>();
		UGridSlot* slot = horizontal_box_container_->AddChildToGrid(horizontal_box);
		if (slot)
		{
			slot->SetRow(i);
			slot->SetHorizontalAlignment(EHorizontalAlignment::HAlign_Center);
			slot->SetVerticalAlignment(EVerticalAlignment::VAlign_Center);
		}
		candidates_item_containers_.Add(horizontal_box);
	}
	for (int32 i = 0; i < candidates_items.Num(); i++)
	{
		UCheckboxButtonWidget* cb = WidgetTree->ConstructWidget<UCheckboxButtonWidget>(check_box_button_class_);
		if (cb)
		{
			UHorizontalBoxSlot* cb_slot = candidates_item_containers_[i / MAX_ROW]->AddChildToHorizontalBox(cb);
			if (cb_slot)
			{
				cb_slot->SetPadding(FMargin(64.f, 16.f));
			}
			cb->SetItem(candidates_items[i]);

			candidates_items_widgets_.Add(cb);
			candidates_items_.Add(candidates_items[i]);
		}

	}
}
