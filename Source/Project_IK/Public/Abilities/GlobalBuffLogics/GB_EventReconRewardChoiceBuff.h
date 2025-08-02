/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 08.01.2025
Summary : Header file for a global buff that increase CombatEndRewardChoice amount by the Recon event.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GlobalBuffLogics/GlobalBuffLogicBase.h"
#include "GB_EventReconRewardChoiceBuff.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UGB_EventReconRewardChoiceBuff : public UGlobalBuffLogicBase
{
	GENERATED_BODY()

public:
	virtual void OnBuffExpired() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 increase_amount = 1;
};
