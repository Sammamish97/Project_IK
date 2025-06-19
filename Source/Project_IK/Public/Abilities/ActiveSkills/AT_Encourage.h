/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 04.19.2025
Summary : Header file for an active skill named Encourage.
					Buffs of attack speed & skill cool-time in a range of allies.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/ActiveSkills/ActiveSkillBase.h"
#include "AT_Encourage.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UAT_Encourage : public UActiveSkillBase
{
	GENERATED_BODY()
public:
	UAT_Encourage();
	virtual bool ActivateSkill(const FTargetResult& TargetResult) override;
};
