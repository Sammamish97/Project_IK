/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.18.2025
Summary : Header file for Shock Javelin active skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Abilities/ActiveSkills/ActiveSkillBase.h"
#include "AT_ShockJavelin.generated.h"

UCLASS()
class PROJECT_IK_API UAT_ShockJavelin : public UActiveSkillBase
{
	GENERATED_BODY()
	
public:
	UAT_ShockJavelin();
	virtual void Decide(const FTargetResult& TargetResult) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector javelin_location_offset_ = FVector(0.f, 0.f, 3000.f);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Skills", meta=(AllowPrivateAccess=true))
	TSubclassOf<class AShockJavelin> javelin_class_;
};
