/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 07.17.2025
Summary : Header file for perk effects that modify combat_end_equipment_reward_num_candidates_.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/PerkEffects/PerkEffectBase.h"
#include "PE_ModifyCombatRewardCandidates.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UPE_ModifyCombatRewardCandidates : public UPerkEffectBase
{
	GENERATED_BODY()
public:
	virtual void ApplyEffect() override;
	virtual void RemoveEffect() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 new_combat_end_equipment_reward_num_candidates_ = 0;
};
