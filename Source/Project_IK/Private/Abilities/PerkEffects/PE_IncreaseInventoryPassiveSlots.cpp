/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 7.21.2025
Summary : Source file for perk effects that increase inventory_passive_skill_unlocked_slots_.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/PerkEffects/PE_IncreaseInventoryPassiveSlots.h"

#include "Subsystems/PerkModifierSubsystem.h"

void UPE_IncreaseInventoryPassiveSlots::ApplyEffect()
{
	UWorld* world = GetWorld();

	if (world)
	{
		UPerkModifierSubsystem* subsystem =
			world->GetGameInstance()->GetSubsystem<UPerkModifierSubsystem>();
		subsystem->SetInventoryPassiveSkillUnlockedSlots(
			subsystem->GetInventoryPassiveSkillUnlockedSlots() + new_inventory_passive_skill_unlocked_slots_);
	}
}

void UPE_IncreaseInventoryPassiveSlots::RemoveEffect()
{
	UWorld* world = GetWorld();

	if (world)
	{
		UPerkModifierSubsystem* subsystem =
			world->GetGameInstance()->GetSubsystem<UPerkModifierSubsystem>();
		subsystem->SetInventoryPassiveSkillUnlockedSlots(
			subsystem->GetInventoryPassiveSkillUnlockedSlots() - new_inventory_passive_skill_unlocked_slots_);
	}
}
