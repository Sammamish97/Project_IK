/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.1.2025
Summary : Source file for Hero Equip Board Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/HeroEquipBoardWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Structs/SpawnData.h"
#include "Subsystems/LevelTransitionSubsystem.h"
#include "WorldSettings/IKGameInstance.h"

#include "UI/WeaponSlotWidget.h"
#include "UI/ActiveSkillSlotWidget.h"
#include "UI/PassiveSkillSlotWidget.h"

void UHeroEquipBoardWidget::SetInventoryWidgetCache(UInventoryWidget* widget_ptr)
{
	inventory_widget_cache_ = widget_ptr;
	TArray<UInventorySlot*> slot_array_ = {weapon_slot_, active_skill_slot_, passive_skill_1_slot_};
	for (auto elem : slot_array_)
	{
		elem->SetInventoryWidgetCache(inventory_widget_cache_);
	}
}

void UHeroEquipBoardWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

//Instance의 Inventory Manager에서 현재 장착된 장비의 정보를 Widget에 Load.
void UHeroEquipBoardWidget::LoadHeroData(int32 hero_idx)
{
	TObjectPtr<UIKGameInstance> ik_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	TObjectPtr<ULevelTransitionSubsystem> transition_system = ik_instance->GetLevelTransitionSubsystem();
	TArray<UInventorySlot*> slot_array_ = {weapon_slot_, active_skill_slot_, passive_skill_1_slot_};

	if(transition_system->GetSpawnData().IsEmpty() == false)
	{
		FSpawnData data_cache = transition_system->GetSpawnData(hero_idx);

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
	}
}

//Widget의 정보를 Instance의 Inventory Manager에 Update.
void UHeroEquipBoardWidget::UpdateHeroData(int32 hero_idx)
{
	TObjectPtr<UIKGameInstance> ik_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	TObjectPtr<ULevelTransitionSubsystem> transition_system = ik_instance->GetLevelTransitionSubsystem();
	
	if(transition_system->GetSpawnData().IsEmpty() == false)
	{
		FSpawnData data_cache = transition_system->GetSpawnData(hero_idx);
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
		
		transition_system->UpdateSpawnDataIdx(hero_idx, data_cache);
	}
}
