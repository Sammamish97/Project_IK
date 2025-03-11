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

#include "Subsystems/LevelTransitionSubsystem.h"
#include "UI/InventorySlot.h"
#include "WorldSettings/IKGameInstance.h"

class UIKGameInstance;

void UEquipBoardWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	owner_equip_array_.Add(weapon_);
	owner_equip_array_.Add(passive_skill_);
	owner_equip_array_.Add(active_skill_);
	owner_equip_array_.Add(oopart_);
	
	weapon_->slot_type_ = EInventorySlotType::Weapon;
	passive_skill_->slot_type_ = EInventorySlotType::PassiveSkill;
	active_skill_->slot_type_ = EInventorySlotType::ActiveSkill;
	oopart_->slot_type_ = EInventorySlotType::Oopart;
}

void UEquipBoardWidget::LoadEquipInventory(int32 hero_idx)
{
	TObjectPtr<UIKGameInstance> ik_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	TObjectPtr<ULevelTransitionSubsystem> transition_system = ik_instance->GetLevelTransitionSubsystem();
	
	if(transition_system->GetSpawnData().IsEmpty() == false)
	{
		FSpawnData data_cache = transition_system->GetSpawnData(hero_idx);
		weapon_->slot_data_.weapon_type = data_cache.weapon_data_.type;
		passive_skill_->slot_data_.passive_skill_type = data_cache.passive_skill_data_.type;
		active_skill_->slot_data_.active_skill_type = data_cache.active_skill_data_.type;
		oopart_->slot_data_.oopart_type = data_cache.oopart_data_.type;
		for (auto& elem : owner_equip_array_)
		{
			elem->SetImageTexture();
		}
	}
}
