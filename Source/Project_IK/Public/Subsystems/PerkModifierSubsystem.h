/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 07.15.2025
Summary : Header file for a subsystem that manages game data modified by perks.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Managers/EnumCluster.h"
#include "PerkModifierSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UPerkModifierSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetNumMaxPull(int32 num_max_pull);
	UFUNCTION(BlueprintPure)
	int32 GetNumMaxPull() const;

	UFUNCTION(BlueprintCallable)
	void SetSeedWeightRarity(ERarity seed_weight_rarity);
	UFUNCTION(BlueprintPure)
	ERarity GetSeedWeightRarity() const;

	UFUNCTION(BlueprintCallable)
	void SetCombatEndHealPercentage(float combat_end_heal_percentage);
	UFUNCTION(BlueprintPure)
	float GetCombatEndHealPercentage() const;

	UFUNCTION(BlueprintCallable)
	void SetCombatEndEquipmentRewardNumCandidates(int32 combat_end_equipment_reward_num_candidates);
	UFUNCTION(BlueprintPure)
	int32 GetCombatEndEquipmentRewardNumCandidates() const;

	UFUNCTION(BlueprintCallable) 
	void SetCombatEndEquipmentRewardMaxChoice(int32 combat_end_equipment_reward_max_choice);
	UFUNCTION(BlueprintPure)
	int32 GetCombatEndEquipmentRewardMaxChoice() const;

protected:
	int32 num_max_pull_ = 0;
	ERarity seed_weight_rarity_ = ERarity::Common;

	float combat_end_heal_percentage_ = 0.f;

	int32 combat_end_equipment_reward_num_candidates_ = 6;
	int32 combat_end_equipment_reward_max_choice_ = 3;
};
