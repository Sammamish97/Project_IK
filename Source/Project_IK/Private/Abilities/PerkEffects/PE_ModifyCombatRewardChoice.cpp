/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 07.17.2025
Summary : Source file for perk effects that modify combat_end_equipment_reward_max_choice_.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/PerkEffects/PE_ModifyCombatRewardChoice.h"

#include "Subsystems/PerkModifierSubsystem.h"

void UPE_ModifyCombatRewardChoice::ApplyEffect()
{
	UWorld* world = GetWorld();
	if (world)
	{
		world->GetGameInstance()->GetSubsystem<UPerkModifierSubsystem>()->SetCombatEndEquipmentRewardMaxChoice(new_combat_end_equipment_reward_max_choice_);
	}
}

void UPE_ModifyCombatRewardChoice::RemoveEffect()
{
}
