/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.28.2025
Summary : Header file for one status buff.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "BuffHandler.h"
#include "Structs/BuffStatusData.h"
#include "BF_TwoStatusBuff.generated.h"

UCLASS(Abstract)
class PROJECT_IK_API UBF_TwoStatusBuff : public UBuffHandler
{
	GENERATED_BODY()
public:
	virtual void ApplyBuff(AUnit* target) override;
	virtual void RemoveBuff(AUnit* target) override;
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Buffs", meta = (AllowPrivateAccess = "true"))
	FBuffStatusData first_buff_status_data_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Buffs", meta = (AllowPrivateAccess = "true"))
	FBuffStatusData second_buff_status_data_;
};
