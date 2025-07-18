/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 07.15.2025
Summary : Source file for a subsystem that manages game data modified by perks.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Subsystems/PerkModifierSubsystem.h"

void UPerkModifierSubsystem::SetNumMaxPull(int32 num_max_pull)
{
	num_max_pull_ = num_max_pull;
}

int32 UPerkModifierSubsystem::GetNumMaxPull() const
{
	return num_max_pull_;
}

void UPerkModifierSubsystem::SetSeedWeightRarity(ERarity seed_weight_rarity)
{
	seed_weight_rarity_ = seed_weight_rarity;
}

ERarity UPerkModifierSubsystem::GetSeedWeightRarity() const
{
	return seed_weight_rarity_;
}

void UPerkModifierSubsystem::SetCombatEndHealPercentage(float combat_end_heal_percentage)
{
	combat_end_heal_percentage_ = combat_end_heal_percentage;
}

float UPerkModifierSubsystem::GetCombatEndHealPercentage() const
{
	return combat_end_heal_percentage_;
}

void UPerkModifierSubsystem::SetCombatEndEquipmentRewardNumCandidates(int32 combat_end_equipment_reward_num_candidates)
{
	combat_end_equipment_reward_num_candidates_ = combat_end_equipment_reward_num_candidates;
}

int32 UPerkModifierSubsystem::GetCombatEndEquipmentRewardNumCandidates() const
{
	return combat_end_equipment_reward_num_candidates_;
}

void UPerkModifierSubsystem::SetCombatEndEquipmentRewardMaxChoice(int32 combat_end_equipment_reward_max_choice)
{
	combat_end_equipment_reward_max_choice_ = combat_end_equipment_reward_max_choice;
}

int32 UPerkModifierSubsystem::GetCombatEndEquipmentRewardMaxChoice() const
{
	return combat_end_equipment_reward_max_choice_;
}
