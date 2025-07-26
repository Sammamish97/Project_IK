/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.22.2025
Summary : Header file for encourage buff.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "BuffHandler.h"
#include "Structs/BuffStatusData.h"
#include "BF_Encourage.generated.h"

UCLASS()
class PROJECT_IK_API UBF_Encourage : public UBuffHandler
{
	GENERATED_BODY()
public:
	virtual void ApplyBuff(AUnit* target) override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Buffs", meta = (AllowPrivateAccess = "true"))
	FBuffStatusData atk_power_stat_data_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Buffs", meta = (AllowPrivateAccess = "true"))
	FBuffStatusData skill_power_stat_data_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Buffs", meta = (AllowPrivateAccess = "true"))
	float duration_ = 0.f;
};
