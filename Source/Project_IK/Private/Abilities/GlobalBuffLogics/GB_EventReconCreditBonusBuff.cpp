/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 08.01.2025
Summary : Source file for a global buff that increase credit bonus.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/GlobalBuffLogics/GB_EventReconCreditBonusBuff.h"

#include "Subsystems/PerkModifierSubsystem.h"

void UGB_EventReconCreditBonusBuff::OnBuffExpired()
{
	UWorld* world = GetWorld();
	if (world)
	{
		UPerkModifierSubsystem* subsystem = world->GetGameInstance()->GetSubsystem<UPerkModifierSubsystem>();
		subsystem->SetCombatEndCreditsBonusPercentage(
			subsystem->GetCombatEndCreditsBonusPercentage() - increased_credit_bonus_
		);
	}
}
