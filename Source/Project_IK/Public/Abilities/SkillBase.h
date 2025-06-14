/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 06/14/2025
Summary : Header file for skill base.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Structs/TargetParameters.h"
#include "Structs/TargetResult.h"
#include "UObject/Object.h"
#include "SkillBase.generated.h"

UCLASS()
class PROJECT_IK_API USkillBase : public UObject
{
	GENERATED_BODY()
public:
	FTargetParameters GetTargetParameters() const;
	float GetCoolTime() const;
	virtual bool ActivateSkill(const FTargetResult& TargetResult);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FTargetParameters target_param_{};

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float cool_time_ = 0.f;
};
