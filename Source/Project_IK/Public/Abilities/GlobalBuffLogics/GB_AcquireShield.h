/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 07.21.2025
Summary : Header file for a global buff that applies shield to a hero when combat begins.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GlobalBuffLogics/GlobalBuffLogicBase.h"
#include "GB_AcquireShield.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECT_IK_API UGB_AcquireShield : public UGlobalBuffLogicBase
{
	GENERATED_BODY()

	bool IsBuffValidOnTarget(UObject* buff_target) override;
	void ApplyBuff(UObject* buff_target) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float shield_amount_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float duration_;
};
