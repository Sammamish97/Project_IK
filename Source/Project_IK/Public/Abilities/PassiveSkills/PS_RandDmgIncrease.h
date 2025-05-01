/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.5.2025
Summary : Header file for the random damage increase skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "PassiveSkillBase.h"
#include "PS_RandDmgIncrease.generated.h"

UCLASS()
class PROJECT_IK_API UPS_RandDmgIncrease : public UPassiveSkillBase
{
	GENERATED_BODY()
public:
	virtual void InitEquipmentSkill(AActor* hero_ref) override;

protected:
	UFUNCTION()
	FDamageData OnEquipmentSkill(FDamageData dmg_data);
};
