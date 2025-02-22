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
#include "ActiveSkillBase.h"
#include "AS_Thunder.generated.h"
UCLASS()
class PROJECT_IK_API UAS_Thunder : public UActiveSkillBase
{
	GENERATED_BODY()
	void RunActiveSkill() override;
	void Thunder(AActor* target);
	
private:
	float damage_;
	float range_;
	//VFX & SFX
};
