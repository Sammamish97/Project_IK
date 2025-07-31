/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.28.2025
Summary : Header file for Close Quaters Mastery.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "BuffHandler.h"
#include "BF_CloseQuatersMastery.generated.h"

UCLASS(Abstract)
class PROJECT_IK_API UBF_CloseQuatersMastery : public UBuffHandler
{
	GENERATED_BODY()
public:
	virtual void ApplyBuff(AUnit* target) override;

private:
	UFUNCTION()
	void CloseQuatersMastery(float& critical_rate);

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	float max_critical_rate_bonus_ = 200.f;

	UPROPERTY(Transient)
	TWeakObjectPtr<AUnit> target_cache_;
};
