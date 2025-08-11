/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 07.26.2025
Summary : Header file for a global buff that apply buff using BF_OneStatusBuff.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GlobalBuffLogics/GlobalBuffLogicBase.h"
#include "GB_ApplyBuffToActor.generated.h"

class UBuffHandler;
class AUnit;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UGB_ApplyBuffToActor : public UGlobalBuffLogicBase
{
	GENERATED_BODY()
public:
	virtual bool IsBuffValidOnTarget(UObject* buff_target) override;
	virtual void ApplyBuff(UObject* buff_target) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AUnit> buff_target_class_;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UBuffHandler> buff_class_;
};
