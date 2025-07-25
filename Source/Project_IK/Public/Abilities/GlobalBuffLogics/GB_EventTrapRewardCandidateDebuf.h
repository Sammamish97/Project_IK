/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 07.24.2025
Summary : Header file for a global buff that decrease CombatEndRewardCandidates amount by the Trap event.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GlobalBuffLogics/GlobalBuffLogicBase.h"
#include "GB_EventTrapRewardCandidateDebuf.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UGB_EventTrapRewardCandidateDebuf : public UGlobalBuffLogicBase
{
	GENERATED_BODY()
	
public:
	virtual void OnBuffExpired() override;

protected:
	// Decrease has been done in Event code.
	// It needs to recover when the event ended.
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 increase_amount = 2;
};
