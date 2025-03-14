/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 3.11.2025
Summary : Source file for Rune Storage widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/RuneStorageWidget.h"

#include "Components/ScrollBox.h"
#include "Components/WrapBox.h"
#include "Kismet/GameplayStatics.h"

#include "Managers/InventoryManager.h"
#include "UI/RuneSlotWidget.h"
#include "WorldSettings/IKGameInstance.h"

void URuneStorageWidget::SetCurSlotNum(int32 input_num)
{
	cur_slot_num_ = input_num;
}

void URuneStorageWidget::UpdateRuneStorage()
{
	if (inventory_manager_cache_ == nullptr)
	{
		TObjectPtr<UIKGameInstance> ik_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		inventory_manager_cache_ = ik_instance->GetInventoryManager();
	}
	auto& rune_storage_data = inventory_manager_cache_->GetRuneStorageData();
	//1. 기존의 존재하는 slot_num에 해당하는 값들 제거.
	for (auto& elem : rune_storage_data)
	{
		if (elem.is_empty == false && elem.slot_number == cur_slot_num_)
		{
			elem = FRuneData();
		}
	}
	
	//2. 빈 자리에 update된 rune들을 삽입.
	for (auto& elem : rune_storage_slots_)
	{
		if (elem->GetRuneData().is_empty == false)
		{
			inventory_manager_cache_->AddRune(elem->GetRuneData());
		}
	}
}

void URuneStorageWidget::LoadRuneStorage(int32 slot_num)
{
	if (inventory_manager_cache_ == nullptr)
	{
		TObjectPtr<UIKGameInstance> ik_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
		inventory_manager_cache_ = ik_instance->GetInventoryManager();
	}
	if (cur_slot_num_ == slot_num)
	{
		return;
	}
	cur_slot_num_ = slot_num;
	UE_LOG(LogTemp, Warning, TEXT("Loading rune storage data: Cur Slot: %d"), cur_slot_num_);
	
	scroll_box_->ClearChildren();
	wrap_box_->ClearChildren();
	
	rune_storage_slots_.Empty();
	rune_storage_slots_.Init(nullptr, inventory_manager_cache_->GetMaxInventorySize());
	auto storage_data = inventory_manager_cache_->GetRuneStorageData();
	
	for(int i = 0; i < storage_data.Num(); i++)
	{
		rune_storage_slots_[i] = CreateWidget<URuneSlotWidget>(GetWorld(), slot_BP_class_);
		rune_storage_slots_[i]->InitRuneSlot(this);
		if (storage_data[i].is_empty == false && cur_slot_num_ == storage_data[i].slot_number)
		{
			rune_storage_slots_[i]->SetRuneData(storage_data[i]);
			UE_LOG(LogTemp, Warning, TEXT("Get available storage data"));
		}
		else
		{
			rune_storage_slots_[i]->SetRuneData(FRuneData(cur_slot_num_));
		}
		rune_storage_slots_[i]->SetImageTexture();
		wrap_box_->AddChild(rune_storage_slots_[i]);
	}
	scroll_box_->AddChild(wrap_box_);
}

int32 URuneStorageWidget::GetCurSlotNum()
{
	return cur_slot_num_;
}
