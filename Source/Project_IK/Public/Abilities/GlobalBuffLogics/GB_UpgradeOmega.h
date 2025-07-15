/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 07.14.2025
Summary : Header file for a global buff that upgrades hero Omega.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GlobalBuffLogics/GlobalBuffLogicBase.h"
#include "GB_UpgradeOmega.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UGB_UpgradeOmega : public UGlobalBuffLogicBase
{
	GENERATED_BODY()
public:
	// A function that returns true if the parameter is expected data such as AActor*, UIKGameMode*
	virtual bool IsBuffValidOnTarget(UObject* buff_target) override;

	// A function that contains real logic of buffs or triggers applying buffs.
	virtual void ApplyBuff(UObject* buff_target) override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float attack_power_scaler_ = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float skill_power_scaler_ = 1.f;
};
