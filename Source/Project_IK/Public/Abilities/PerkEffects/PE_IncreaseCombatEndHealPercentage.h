/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 07.17.2025
Summary : Header file for perk effects that Increase combat_end_heal_percentage_ .

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/PerkEffects/PerkEffectBase.h"
#include "PE_IncreaseCombatEndHealPercentage.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UPE_IncreaseCombatEndHealPercentage : public UPerkEffectBase
{
	GENERATED_BODY()
public:
	virtual void ApplyEffect() override;
	virtual void RemoveEffect() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float new_combat_end_heal_percentage_ = 0;
};
