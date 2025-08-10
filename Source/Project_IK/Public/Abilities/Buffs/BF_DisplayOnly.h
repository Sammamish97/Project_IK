/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.31.2025
Summary : Header file for Display Only buff.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "BuffHandler.h"
#include "BF_DisplayOnly.generated.h"

UCLASS()
class PROJECT_IK_API UBF_DisplayOnly : public UBuffHandler
{
	GENERATED_BODY()
public:
	virtual void ApplyBuff(AUnit* target) override;
	virtual void RemoveBuff(AUnit* target) override;

private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	bool is_permanent_ = false;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	float duration_;
};
