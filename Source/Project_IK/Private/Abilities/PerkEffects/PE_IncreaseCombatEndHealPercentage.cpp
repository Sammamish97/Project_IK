/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 07.17.2025
Summary : Source file for perk effects that Increase combat_end_heal_percentage_ .

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/PerkEffects/PE_IncreaseCombatEndHealPercentage.h"
#include "Subsystems/PerkModifierSubsystem.h"

void UPE_IncreaseCombatEndHealPercentage::ApplyEffect()
{
	UWorld* world = GetWorld();

	if (world)
	{
		UPerkModifierSubsystem* subsystem =
			world->GetGameInstance()->GetSubsystem<UPerkModifierSubsystem>();
		subsystem->SetCombatEndHealPercentage(
			subsystem->GetCombatEndHealPercentage() + new_combat_end_heal_percentage_);
	}
}

void UPE_IncreaseCombatEndHealPercentage::RemoveEffect()
{
	UWorld* world = GetWorld();

	if (world)
	{
		UPerkModifierSubsystem* subsystem =
			world->GetGameInstance()->GetSubsystem<UPerkModifierSubsystem>();
		subsystem->SetCombatEndHealPercentage(
			subsystem->GetCombatEndHealPercentage() - new_combat_end_heal_percentage_);
	}
}
