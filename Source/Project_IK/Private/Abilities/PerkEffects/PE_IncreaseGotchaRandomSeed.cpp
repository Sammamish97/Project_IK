/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 7.15.2025
Summary : Source file for perk effects that Increase gotcha seed_weight_rarity_.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/PerkEffects/PE_IncreaseGotchaRandomSeed.h"
#include "Subsystems/PerkModifierSubsystem.h"

void UPE_IncreaseGotchaRandomSeed::ApplyEffect()
{
	UWorld* world = GetWorld();
	if (world)
	{
		world->GetGameInstance()->GetSubsystem<UPerkModifierSubsystem>()->SetSeedWeightRarity(new_seed_weight_rarity_);
	}
}

void UPE_IncreaseGotchaRandomSeed::RemoveEffect()
{
	// This code may differ if there are several perk nodes that have this effects.
	UWorld* world = GetWorld();
	if (world)
	{
		world->GetGameInstance()->GetSubsystem<UPerkModifierSubsystem>()->SetSeedWeightRarity(old_seed_weight_rarity_);
	}
}
