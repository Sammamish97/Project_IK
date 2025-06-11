/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.21.2024
Summary : Header file for Test skill class.
					The first skill class to test it.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "ActiveSkills/ActiveSkillBase.h"

#include "Structs/TargetResult.h"
#include "MyTestSkill.generated.h"

UCLASS()
class PROJECT_IK_API UMyTestSkill : public UActiveSkillBase
{
	GENERATED_BODY()
	
public:
	UMyTestSkill();

	virtual void Decide(const FTargetResult& TargetResult) override;
};
