/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.22.2025
Summary : Header file for Thunder Active Skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Abilities/ActiveSkills/ActiveSkillBase.h"
#include "Structs/TargetResult.h"
#include "AT_Thunder.generated.h"


UCLASS()
class PROJECT_IK_API UAT_Thunder : public UActiveSkillBase
{
	GENERATED_BODY()
	UAT_Thunder();
	virtual TOptional<FTargetParameters> ActivateSkill(const FTargetResult& TargetResult) override;

protected:
	float damage_ = 0.f;
};
