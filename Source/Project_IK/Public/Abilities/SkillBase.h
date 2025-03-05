/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.21.2024
Summary : Header file for Skill base class.
					It will be used like a pure virtual class. A skill class will derived it.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "Components/TargetingComponent.h"

#include "SkillBase.generated.h"

UCLASS(Blueprintable)
class PROJECT_IK_API USkillBase : public UObject
{
	GENERATED_BODY()
	
public:
	void InitActiveSkill(AActor* skill_owner);

	FTargetParameters GetTargetParameters() const;
	float GetCooltime() const;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	bool ActivateSkill(const FTargetResult& TargetResult);

	virtual bool ActivateSkill_Implementation(const FTargetResult& TargetResult) PURE_VIRTUAL(USkillBase::ActivateSkill_Implementation, return true;);

protected:
	UPROPERTY(VisibleAnywhere)
	FTargetParameters target_param_{};

	UPROPERTY(VisibleAnywhere)
	float cool_time_ = 0.f;

	UPROPERTY(VisibleAnywhere)
	AActor* skill_owner_ = nullptr;
};
