/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 07.24.2025
Summary : Source file for a global buff that decrease CombatEndRewardCandidates amount by the Trap event.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/GlobalBuffLogics/GB_EventTrapRewardCandidateDebuf.h"

#include "Subsystems/PerkModifierSubsystem.h"

void UGB_EventTrapRewardCandidateDebuf::OnBuffExpired()
{
	UWorld* world = GetWorld();
	if (world)
	{
		UPerkModifierSubsystem* subsystem = world->GetGameInstance()->GetSubsystem<UPerkModifierSubsystem>();
		subsystem->SetCombatEndEquipmentRewardNumCandidates(
			subsystem->GetCombatEndEquipmentRewardNumCandidates() + increase_amount
		);
	}
}
