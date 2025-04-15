/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.15.2025
Summary : Header file for Accelerate Active Skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Abilities/SkillBase.h"
#include "AT_Accelerate.generated.h"
UCLASS()
class PROJECT_IK_API UAT_Accelerate : public USkillBase
{
	GENERATED_BODY()

public:
	UAT_Accelerate();
	virtual bool ActivateSkill_Implementation(const FTargetResult& TargetResult) override;

private:
	float shield_amount_ = 100.f;
	float attack_speed_increase_amount_ = 2.f;
	float buff_duration_ = 2.f;
};
