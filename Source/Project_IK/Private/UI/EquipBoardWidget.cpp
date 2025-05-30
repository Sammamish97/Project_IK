/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 3.10.2025
Summary : Source file for Equip Board widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/EquipBoardWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Managers/EnumCluster.h"
#include "Structs/SpawnData.h"
#include "Managers/DataTableManager.h"

#include "Subsystems/LevelTransitionSubsystem.h"
#include "UI/InventorySlot.h"
#include "WorldSettings/IKGameInstance.h"
void UEquipBoardWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//TODO: Construct마다 하는것이 아닌, 단 한번만 하는 방법이 필요하다.
	weapon_->slot_type_ = EInventorySlotType::WeaponBoardSlot;
	weapon_->slot_data_.gear_type = EGearType::Weapon;
	
	passive_skill_->slot_type_ = EInventorySlotType::PassiveSkillBoardSlot;
	passive_skill_->slot_data_.gear_type = EGearType::PassiveSkill;

	active_skill_->slot_type_ = EInventorySlotType::ActiveSkillBoardSlot;
	active_skill_->slot_data_.gear_type = EGearType::ActiveSkill;
}


void UEquipBoardWidget::SetCurHeroIdx(int32 hero_idx)
{
	cur_hero_idx_ = hero_idx;
}

void UEquipBoardWidget::LoadEquipBoard()
{
	slot_array_ = {weapon_, passive_skill_, active_skill_};
	for (auto& elem : slot_array_)
	{
		elem->ClearData();
	}
	
	weapon_->slot_data_.gear_type = EGearType::Weapon;
	passive_skill_->slot_data_.gear_type = EGearType::PassiveSkill;
	active_skill_->slot_data_.gear_type = EGearType::ActiveSkill;
	
	TObjectPtr<UIKGameInstance> ik_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	TObjectPtr<ULevelTransitionSubsystem> transition_system = ik_instance->GetLevelTransitionSubsystem();
	
	if(transition_system->GetSpawnData().IsEmpty() == false)
	{
		FSpawnData data_cache = transition_system->GetSpawnData(cur_hero_idx_);

		if (data_cache.weapon_data_.IsSet())
		{
			weapon_->slot_data_.weapon_type = data_cache.weapon_data_.GetValue().type;
			weapon_->slot_data_.is_empty = false;
		}
		if (data_cache.passive_skill_data_.IsSet())
		{
			passive_skill_->slot_data_.passive_skill_type = data_cache.passive_skill_data_.GetValue().type;
			passive_skill_->slot_data_.is_empty = false;
		}
		if (data_cache.active_skill_data_.IsSet())
		{
			active_skill_->slot_data_.active_skill_type = data_cache.active_skill_data_.GetValue().type;
			active_skill_->slot_data_.is_empty = false;
		}
		for (auto& elem : slot_array_)
		{
			elem->SetImageTexture();
		}
	}
}

void UEquipBoardWidget::UpdateEquipBoard()
{
	TObjectPtr<UIKGameInstance> ik_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	TObjectPtr<ULevelTransitionSubsystem> transition_system = ik_instance->GetLevelTransitionSubsystem();
	TObjectPtr<UDataTableManager> data_table_manager = ik_instance->GetDataTableManager();
	
	if(transition_system->GetSpawnData().IsEmpty() == false)
	{
		FSpawnData data_cache = transition_system->GetSpawnData(cur_hero_idx_);
		if (weapon_->slot_data_.is_empty == false)
		{
			data_cache.weapon_data_ = data_table_manager->GetWeaponStatusData(weapon_->slot_data_.weapon_type);
		}
		else
		{
			data_cache.weapon_data_.Reset();
		}
		
		if (active_skill_->slot_data_.is_empty == false)
		{
			data_cache.active_skill_data_ = data_table_manager->GetActiveSkillData(active_skill_->slot_data_.active_skill_type);
		}
		else
		{
			data_cache.active_skill_data_.Reset();
		}
		if (passive_skill_->slot_data_.is_empty == false)
		{
			data_cache.passive_skill_data_ = data_table_manager->GetPassiveSkillData(passive_skill_->slot_data_.passive_skill_type);
		}
		else
		{
			data_cache.passive_skill_data_.Reset();
		}
		transition_system->UpdateSpawnDataIdx(cur_hero_idx_, data_cache);
	}
}
