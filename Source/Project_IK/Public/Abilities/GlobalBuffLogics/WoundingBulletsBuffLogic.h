/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 03.12.2025
Summary : Header file for a global buff that remains bleeding on targets damaged.

Licensed under the MIT Lice	nse.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GlobalBuffLogics/GlobalBuffLogicBase.h"
#include "WoundingBulletsBuffLogic.generated.h"

struct FDamageDage;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UWoundingBulletsBuffLogic : public UGlobalBuffLogicBase
{
	GENERATED_BODY()
	
public:

	bool IsBuffValidOnTarget(UObject* buff_target) override;
	void ApplyBuff(UObject* buff_target) override;

protected:
	UFUNCTION()
	FDamageData ApplyBleeding(FDamageData data);
};
