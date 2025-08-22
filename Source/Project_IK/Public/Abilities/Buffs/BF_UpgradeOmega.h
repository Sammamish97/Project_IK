/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 07.28.2025
Summary : Header file for a buff that upgrades hero Omega.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Buffs/BuffHandler.h"
#include "BF_UpgradeOmega.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UBF_UpgradeOmega : public UBuffHandler
{
	GENERATED_BODY()
public:
	virtual void ApplyBuff(AUnit* target) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float attack_power_scaler_ = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float skill_power_scaler_ = 1.f;
};
