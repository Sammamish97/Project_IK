/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 7.18.2025
Summary : Source file for perk effects that Increase combat_end_credits_bonus_percentage_.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/PerkEffects/PE_IncreaseCombatEndCreditsBonus.h"

#include "Subsystems/PerkModifierSubsystem.h"

void UPE_IncreaseCombatEndCreditsBonus::ApplyEffect()
{
	UWorld* world = GetWorld();

	if (world)
	{
		UPerkModifierSubsystem* subsystem =
			world->GetGameInstance()->GetSubsystem<UPerkModifierSubsystem>();
		subsystem->SetCombatEndCreditsBonusPercentage(
			subsystem->GetCombatEndCreditsBonusPercentage() + new_combat_end_credits_bonus_percentage_);
	}
}

void UPE_IncreaseCombatEndCreditsBonus::RemoveEffect()
{
	UWorld* world = GetWorld();

	if (world)
	{
		UPerkModifierSubsystem* subsystem =
			world->GetGameInstance()->GetSubsystem<UPerkModifierSubsystem>();
		subsystem->SetCombatEndCreditsBonusPercentage(
			subsystem->GetCombatEndCreditsBonusPercentage() - new_combat_end_credits_bonus_percentage_);
	}
}
