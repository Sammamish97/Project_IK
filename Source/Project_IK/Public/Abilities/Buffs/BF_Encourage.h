/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.28.2025
Summary : Header file for encourage.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "BF_TwoStatusBuff.h"
#include "BF_Encourage.generated.h"

UCLASS()
class PROJECT_IK_API UBF_Encourage : public UBF_TwoStatusBuff
{
	GENERATED_BODY()
public:
	virtual void ApplyBuff(AUnit* target) override;
	
private:
	UPROPERTY(EditDefaultsOnly)
	float shield_amount_;
};
