/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 7.15.2025
Summary : Source file for perk effects that modify gotcha num_max_pull_.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/PerkEffects/PE_ModifyGotchaNumMaxPull.h"

#include "Subsystems/PerkModifierSubsystem.h"

void UPE_ModifyGotchaNumMaxPull::ApplyEffect()
{
	UWorld* world = GetWorld();
	if (world)
	{
		world->GetGameInstance()->GetSubsystem<UPerkModifierSubsystem>()->SetNumMaxPull(new_num_max_pull_);
	}
}

void UPE_ModifyGotchaNumMaxPull::RemoveEffect()
{
}
