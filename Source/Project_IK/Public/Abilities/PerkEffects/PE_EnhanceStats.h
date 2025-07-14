/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 7.13.2025
Summary : Header file for perk effects that enhance hero stat data.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Managers/EnumCluster.h"
#include "Abilities/PerkEffects/PerkEffectBase.h"
#include "PE_EnhanceStats.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UPE_EnhanceStats : public UPerkEffectBase
{
	GENERATED_BODY()
public:
	virtual void ApplyEffect() override;
	virtual void RemoveEffect() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PerkData")
	ECharacterStatType stat_;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PerkData")
	float modifier_;
	
};
