/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 3.10.2025
Summary : Source file for Equip Board widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/EquipBoardWidget.h"

#include "Managers/EnumCluster.h"
#include "UI/InventorySlot.h"

void UEquipBoardWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	weapon_->slot_type_ = EInventorySlotType::Weapon;
	passive_skill_->slot_type_ = EInventorySlotType::PassiveSkill;
	active_skill_->slot_type_ = EInventorySlotType::ActiveSkill;
	oopart_->slot_type_ = EInventorySlotType::Oopart;

	equip_array_.Empty();
	equip_array_.Add(weapon_);
	equip_array_.Add(passive_skill_);
	equip_array_.Add(active_skill_);
	equip_array_.Add(oopart_);
}
