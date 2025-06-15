/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.22.2025
Summary : Header file for the Instant Repair Support SKill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "SupportSkillBase.h"
#include "SP_InstantRepair.generated.h"

UCLASS()
class PROJECT_IK_API USP_InstantRepair : public USupportSkillBase
{
	GENERATED_BODY()
public:
	USP_InstantRepair();
	virtual TOptional<FTargetParameters> ActivateSkill(const FTargetResult& TargetResult) override;
	
private:
	float healing_amount_ = 100.f;
};
