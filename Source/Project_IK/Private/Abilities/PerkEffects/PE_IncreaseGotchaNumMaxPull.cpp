/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 7.15.2025
Summary : Source file for perk effects that Increase gotcha num_max_pull_.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/PerkEffects/PE_IncreaseGotchaNumMaxPull.h"

#include "Subsystems/PerkModifierSubsystem.h"

void UPE_IncreaseGotchaNumMaxPull::ApplyEffect()
{
	UWorld* world = GetWorld();

	if (world)
	{
		UPerkModifierSubsystem* subsystem =
			world->GetGameInstance()->GetSubsystem<UPerkModifierSubsystem>();
		subsystem->SetNumMaxPull(
			subsystem->GetNumMaxPull() + new_num_max_pull_);
	}
}

void UPE_IncreaseGotchaNumMaxPull::RemoveEffect()
{
	UWorld* world = GetWorld();

	if (world)
	{
		UPerkModifierSubsystem* subsystem =
			world->GetGameInstance()->GetSubsystem<UPerkModifierSubsystem>();
		subsystem->SetNumMaxPull(
			subsystem->GetNumMaxPull() - new_num_max_pull_);
	}
}
