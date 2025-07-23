/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.23.2025
Summary : Header file for Berserker buff.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "BuffBase.h"
#include "Structs/BuffStatusData.h"
#include "BF_Berserker.generated.h"

UCLASS()
class PROJECT_IK_API UBF_Berserker : public UBuffBase
{
	GENERATED_BODY()
public:
	virtual void ApplyBuff(AUnit* target) override;
	virtual void RemoveBuff(AUnit* target) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Buffs", meta = (AllowPrivateAccess = "true"))
	FBuffStatusData atk_speed_stat_data_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Buffs", meta = (AllowPrivateAccess = "true"))
	FBuffStatusData vamp_stat_data_;
};
