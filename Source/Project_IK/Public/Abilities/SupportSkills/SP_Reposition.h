/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.1.2025
Summary : Header file for the Instant Repair Support SKill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "SupportSkillBase.h"
#include "SP_Reposition.generated.h"

UCLASS()
class PROJECT_IK_API USP_Reposition : public USupportSkillBase
{
	GENERATED_BODY()
public:
	USP_Reposition();
	virtual void Decide(const FTargetResult& TargetResult) override;
	virtual void Reset() override;

private:
	FTargetParameters reposition_location_params_ = FTargetParameters();
	TObjectPtr<class AHeroBase> selected_hero_ = nullptr;
};