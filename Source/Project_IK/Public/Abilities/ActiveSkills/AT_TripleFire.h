/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.12.2025
Summary : Header file for TripleFire Active Skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Abilities/SkillBase.h"
#include "AT_TripleFire.generated.h"

UCLASS()
class PROJECT_IK_API UAT_TripleFire : public USkillBase
{
	GENERATED_BODY()

public:
	UAT_TripleFire();
	virtual bool ActivateSkill_Implementation(const FTargetResult& TargetResult) override;
};
