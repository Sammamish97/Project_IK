/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 07.14.2025
Summary : Header file for a global buff that upgrades hero Alpha.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GlobalBuffLogics/GlobalBuffLogicBase.h"
#include "GB_UpgradeAlpha.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UGB_UpgradeAlpha : public UGlobalBuffLogicBase
{
	GENERATED_BODY()
public:
	// A function that returns true if the parameter is expected data such as AActor*, UIKGameMode*
	virtual bool IsBuffValidOnTarget(UObject* buff_target) override;

	// A function that contains real logic of buffs or triggers applying buffs.
	virtual void ApplyBuff(UObject* buff_target) override;

protected:
};
