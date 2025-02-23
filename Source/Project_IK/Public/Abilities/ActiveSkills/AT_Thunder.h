// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/SkillBase.h"
#include "AT_Thunder.generated.h"

/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.22.2025
Summary : Header file for Thunder Active Skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
UCLASS()
class PROJECT_IK_API UAT_Thunder : public USkillBase
{
	GENERATED_BODY()
	UAT_Thunder();
	virtual bool ActivateSkill_Implementation(const FTargetResult& TargetResult) override;

private:
	float damage_;
};
