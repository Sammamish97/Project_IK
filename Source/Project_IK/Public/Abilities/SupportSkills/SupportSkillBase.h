/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.22.2025
Summary : Header file for the Support Skill Base.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Abilities/SkillBase.h"
#include "Structs/SupportSkillData.h"
#include "UObject/Object.h"
#include "SupportSkillBase.generated.h"

UCLASS(Abstract, Blueprintable)
class PROJECT_IK_API USupportSkillBase : public USkillBase
{
	GENERATED_BODY()
	
public:
	void InitSupportSkill(const FSupportSkillData& skill_data);
	float GetCost() const;
	const FSupportSkillData& GetSupportSkillData() const;
	virtual bool ActivateSkill(const FTargetResult& TargetResult) override;

protected:
	UPROPERTY(Transient)
	FSupportSkillData skill_data_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float cost_ = 0.f;
};
