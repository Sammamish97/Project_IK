/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 10.19.2024
Summary : Source file for Item inventory.
					It contains a technical data of items.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/ItemInventory.h"
#include "Abilities/Item.h"

#include "Blueprint/UserWidget.h"
#include "UI/ItemKeepOrDiscardWidget.h"

void UItemInventory::AddItem(UItem* item, TFunction<void()> OnConfirm)
{
	if (item_inventory_.Num() < INVENTORY_CAPACITY)
	{
		if (item)
		{
			item_inventory_.Add(item);
		}
		if (OnConfirm)
		{
			OnConfirm();
		}
	}
	else
	{
		CallKeepDiscardUI(item, OnConfirm);
	}
}

void UItemInventory::AddItem(FItemData item_data, TFunction<void()> OnConfirm)
{
	if (item_inventory_.Num() < INVENTORY_CAPACITY)
	{
		UItem* item = NewObject<UItem>(this, item_class_);
		item->InitializeItemUsingData(item_data);

		item_inventory_.Add(item);
		OnConfirm();
	}
	else
	{
		CallKeepDiscardUI(item_data, OnConfirm);
	}
}

void UItemInventory::AddItems(TArray<FItemData> item_data, TFunction<void()> OnConfirm)
{
	if (item_data.Num() + item_inventory_.Num() <= INVENTORY_CAPACITY)
	{
		for (int32 i = 0; i < item_data.Num(); ++i)
		{
			UItem* item = NewObject<UItem>(this, item_class_);
			item->InitializeItemUsingData(item_data[i]);

			item_inventory_.Add(item);
		}
		OnConfirm();
	}
	else
	{
		CallKeepDiscardUI(item_data, OnConfirm);
	}
}

void UItemInventory::UseItem(int32 item_idx, FTargetResult target_result)
{
	if (item_inventory_.IsValidIndex(item_idx))
	{
		item_inventory_[item_idx]->UseItem(GetWorld(), target_result);
		RemoveItem(item_idx);
	}
}

UItem* UItemInventory::GetItem(int32 index) const
{
	if (item_inventory_.IsValidIndex(index))
	{
		return item_inventory_[index].Get();
	}

	return nullptr;
}

void UItemInventory::RemoveItem(int32 index)
{
	if (item_inventory_.IsValidIndex(index))
	{
		item_inventory_.RemoveAt(index);
	}
}

void UItemInventory::ClearItems()
{
	item_inventory_.Empty();
}

void UItemInventory::CallKeepDiscardUI(UItem* item_added, TFunction<void()> OnConfirm)
{
	FItemData data = item_added->GetData();
	CallKeepDiscardUI(data, OnConfirm);
}

void UItemInventory::CallKeepDiscardUI(FItemData item_added, TFunction<void()> OnConfirm)
{
	TArray<FItemData> item_added_data{ item_added };
	CallKeepDiscardUI(item_added_data, OnConfirm);
}

void UItemInventory::CallKeepDiscardUI(TArray<FItemData> item_added, TFunction<void()> OnConfirm)
{
	OnConfirm_ = OnConfirm;
	if (item_keep_discard_class_)
	{
		item_keep_discard_ = CreateWidget<UItemKeepOrDiscardWidget>(GetWorld(), item_keep_discard_class_);
		if (item_keep_discard_)
		{
			TArray<FItemData> inventory_data;
			for (int32 i = 0; i < item_inventory_.Num(); i++)
			{
				inventory_data.Add(item_inventory_[i]->GetData());
			}
			item_keep_discard_->UpdateItems(inventory_data, item_added);
			item_keep_discard_->OnConfirmed.AddDynamic(this, &UItemInventory::OnKeepDiscardFinished);

			item_keep_discard_->AddToViewport();
		}
	}
}

void UItemInventory::OnKeepDiscardFinished(TArray<FItemData> item_data)
{	
	ClearItems();
	for (int32 i = 0; i < item_data.Num(); i++)
	{
		UItem* item = NewObject<UItem>(this, item_class_);
		item->InitializeItemUsingData(item_data[i]);

		item_inventory_.Add(item);
	}

	if (OnConfirm_)
	{
		OnConfirm_();
	}

	ClearItemKeepOrDiscardWidget();
}

void UItemInventory::ClearItemKeepOrDiscardWidget()
{
	if (item_keep_discard_)
	{
		item_keep_discard_->OnConfirmed.RemoveAll(this);
		item_keep_discard_ = nullptr;
	}
}
