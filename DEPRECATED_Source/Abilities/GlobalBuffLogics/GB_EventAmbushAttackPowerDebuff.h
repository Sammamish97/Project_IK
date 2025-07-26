/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 07.23.2025
Summary : Header file for a global buff that decrease AttackPower by the Ambush event.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GlobalBuffLogics/GlobalBuffLogicBase.h"
#include "GB_EventAmbushAttackPowerDebuff.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UGB_EventAmbushAttackPowerDebuff : public UGlobalBuffLogicBase
{
	GENERATED_BODY()
public:

	bool IsBuffValidOnTarget(UObject* buff_target) override;
	void ApplyBuff(UObject* buff_target) override;
};
