/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.24.2025
Summary : Header file for one Maintain support skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "SupportSkillBase.h"
#include "SP_Maintain.generated.h"

UCLASS()
class PROJECT_IK_API USP_Maintain : public USupportSkillBase
{
	GENERATED_BODY()
public:
	USP_Maintain();
	virtual bool ActivateSkill(const FTargetResult& TargetResult) override;
};
