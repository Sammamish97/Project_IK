/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 7.15.2025
Summary : Source file for perk effects that modify gotcha seed_weight_rarity_.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/PerkEffects/PE_ModifyGotchaRandomSeed.h"
#include "Subsystems/GotchaSubsystem.h"

void UPE_ModifyGotchaRandomSeed::ApplyEffect()
{
	UWorld* world = GetWorld();
	if (world)
	{
		world->GetGameInstance()->GetSubsystem<UGotchaSubsystem>()->SetSeedWeightRarity(new_seed_weight_rarity_);
	}
}

void UPE_ModifyGotchaRandomSeed::RemoveEffect()
{
}
