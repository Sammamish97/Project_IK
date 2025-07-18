/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 07.17.2025
Summary : Source file for perk effects that modify combat_end_heal_percentage_ .

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/PerkEffects/PE_ModifyCombatEndHealPercentage.h"
#include "Subsystems/PerkModifierSubsystem.h"

void UPE_ModifyCombatEndHealPercentage::ApplyEffect()
{
	UWorld* world = GetWorld();
	if (world)
	{
		world->GetGameInstance()->GetSubsystem<UPerkModifierSubsystem>()->SetCombatEndHealPercentage(new_combat_end_heal_percentage_);
	}
}

void UPE_ModifyCombatEndHealPercentage::RemoveEffect()
{

}
