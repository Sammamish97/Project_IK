/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.22.2025
Summary : Header file for the support fire Support Skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "SupportSkillBase.h"
#include "Structs/DamageData.h"
#include "SP_SupportFire.generated.h"

UCLASS()
class PROJECT_IK_API USP_SupportFire : public USupportSkillBase
{
	GENERATED_BODY()
public:
	USP_SupportFire();
	virtual bool ActivateSkill(const FTargetResult& TargetResult) override;

private:
	FDamageData dmg_data_;
};
