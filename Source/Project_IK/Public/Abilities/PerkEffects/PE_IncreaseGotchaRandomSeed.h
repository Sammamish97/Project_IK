/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 7.15.2025
Summary : Header file for perk effects that Increase gotcha seed_weight_rarity_.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/PerkEffects/PerkEffectBase.h"
#include "Managers/EnumCluster.h"
#include "PE_IncreaseGotchaRandomSeed.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UPE_IncreaseGotchaRandomSeed : public UPerkEffectBase
{
	GENERATED_BODY()
public:
	virtual void ApplyEffect() override;
	virtual void RemoveEffect() override;
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ERarity new_seed_weight_rarity_ = ERarity::Rare;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ERarity old_seed_weight_rarity_ = ERarity::Common;
};
