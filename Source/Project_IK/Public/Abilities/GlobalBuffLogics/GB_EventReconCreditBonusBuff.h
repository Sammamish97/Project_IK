/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 08.01.2025
Summary : Source file for a global buff that increase credit bonus.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GlobalBuffLogics/GlobalBuffLogicBase.h"
#include "GB_EventReconCreditBonusBuff.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UGB_EventReconCreditBonusBuff : public UGlobalBuffLogicBase
{
	GENERATED_BODY()

public:
	virtual void OnBuffExpired() override;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float increased_credit_bonus_ = 0.2f;
};
