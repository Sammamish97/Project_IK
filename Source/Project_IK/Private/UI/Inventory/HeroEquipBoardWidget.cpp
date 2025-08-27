/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.1.2025
Summary : Source file for Hero Equip Board Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/Inventory/HeroEquipBoardWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Structs/SpawnData.h"
#include "Subsystems/LevelTransitionSubsystem.h"
#include "WorldSettings/IKGameInstance.h"

#include "UI/InventorySlots/WeaponSlotWidget.h"
#include "UI/InventorySlots/ActiveSkillSlotWidget.h"
#include "UI/InventorySlots/PassiveSkillSlotWidget.h"

void UHeroEquipBoardWidget::InitHeroEquipBoard(UInventoryWidget* widget_ptr, EHeroType hero_type)
{
	hero_type_ = hero_type;
	inventory_widget_cache_ = widget_ptr;
	TArray<UInventorySlot*> slot_array_ = {weapon_slot_, active_skill_slot_, passive_skill_1_slot_, passive_skill_2_slot_, passive_skill_3_slot_};
	for (auto elem : slot_array_)
	{
		elem->InitInventorySlot(inventory_widget_cache_, true, hero_type);
	}
}


void UHeroEquipBoardWidget::LoadHeroData()
{
	TObjectPtr<UIKGameInstance> ik_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	TObjectPtr<ULevelTransitionSubsystem> transition_system = ik_instance->GetLevelTransitionSubsystem();

	if(transition_system->GetSpawnData().IsEmpty() == false)
	{
		FSpawnData data_cache = transition_system->GetSpawnData(hero_type_);

		if (data_cache.weapon_data_.IsSet())
		{
			weapon_slot_->SetWeaponSlotData(data_cache.weapon_data_.GetValue());
		}
		if (data_cache.active_skill_data_.IsSet())
		{
			active_skill_slot_->SetActiveSkillSlotData(data_cache.active_skill_data_.GetValue());
		}
		if (data_cache.passive_skill_data_1_.IsSet())
		{
			passive_skill_1_slot_->SetPassiveSkillSlotData(data_cache.passive_skill_data_1_.GetValue());
		}
		if (data_cache.passive_skill_data_2_.IsSet())
		{
			passive_skill_2_slot_->SetPassiveSkillSlotData(data_cache.passive_skill_data_2_.GetValue());

		}
		if (data_cache.passive_skill_data_3_.IsSet())
		{
			passive_skill_3_slot_->SetPassiveSkillSlotData(data_cache.passive_skill_data_3_.GetValue());
		}
	}
}

void UHeroEquipBoardWidget::UpdateHeroData()
{
	TObjectPtr<UIKGameInstance> ik_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	TObjectPtr<ULevelTransitionSubsystem> transition_system = ik_instance->GetLevelTransitionSubsystem();
	
	if(transition_system->GetSpawnData().IsEmpty() == false)
	{
		FSpawnData data_cache = transition_system->GetSpawnData(hero_type_);
		if (weapon_slot_->IsEmpty() == false)
		{
			data_cache.weapon_data_ = weapon_slot_->GetStoredWeaponData();
		}
		else
		{
			data_cache.weapon_data_.Reset();
		}
		
		if (active_skill_slot_->IsEmpty() == false)
		{
			data_cache.active_skill_data_ = active_skill_slot_->GetStoredActiveSkillData();
		}
		else
		{
			data_cache.active_skill_data_.Reset();
		}
		
		if (passive_skill_1_slot_->IsEmpty() == false)
		{
			data_cache.passive_skill_data_1_ = passive_skill_1_slot_->GetStoredPassiveSkillData();
		}
		else
		{
			data_cache.passive_skill_data_1_.Reset();
		}

		if (passive_skill_2_slot_->IsEmpty() == false)
		{
			data_cache.passive_skill_data_2_ = passive_skill_2_slot_->GetStoredPassiveSkillData();
		}
		else
		{
			data_cache.passive_skill_data_2_.Reset();
		}

		if (passive_skill_3_slot_->IsEmpty() == false)
		{
			data_cache.passive_skill_data_3_ = passive_skill_3_slot_->GetStoredPassiveSkillData();
		}
		else
		{
			data_cache.passive_skill_data_3_.Reset();
		}
		
		transition_system->UpdateSpawnDataIdx(hero_type_, data_cache);
	}
}

bool UHeroEquipBoardWidget::CheckDuplicatedPassiveSkill(EPassiveSkillType type)
{
	for (const auto& elem : {passive_skill_1_slot_, passive_skill_2_slot_, passive_skill_3_slot_})
	{
		if (elem->GetIsEnabled())
		{
			if (elem->GetStoredPassiveSkillData().type_ == type)
			{
				return true;
			}
		}
	}
	return false;
}

void UHeroEquipBoardWidget::SetAvailablePassiveSkillAmount(int32 amount)
{
	TArray passive_skill_slot_array = {passive_skill_1_slot_, passive_skill_2_slot_, passive_skill_3_slot_};
	for (int32 i = amount; i < 3; ++i)
	{
		passive_skill_slot_array[i]->SetIsEnabled(false);
	}
}

void UHeroEquipBoardWidget::ToggleReadOnly(bool is_read_only)
{
	TArray<UInventorySlot*> slot_array = {weapon_slot_, active_skill_slot_, passive_skill_1_slot_, passive_skill_2_slot_, passive_skill_3_slot_};
	for (const auto& elem : slot_array)
	{
		elem->SetIsReadOnly(is_read_only);
	}
}
