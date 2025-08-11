/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 07.28.2025
Summary : Source file for a buff that upgrades hero Beta.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Buffs/BuffHandler.h"
#include "Structs/BuffStatusData.h"
#include "BF_UpgradeBeta.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UBF_UpgradeBeta : public UBuffHandler
{
	GENERATED_BODY()
public:
	virtual void ApplyBuff(AUnit* target) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float scaler_ = 2.f;
};
