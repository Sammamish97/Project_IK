/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.28.2025
Summary : Header file for the Composed passive skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "BuffHandler.h"
#include "Structs/BuffStatusData.h"
#include "BF_Composed.generated.h"

UCLASS()
class PROJECT_IK_API UBF_Composed : public UBuffHandler
{
	GENERATED_BODY()
public:
	virtual void ApplyBuff(AUnit* target) override;
	virtual void RemoveBuff(AUnit* target) override;
	
private:
	UPROPERTY(EditDefaultsOnly)
	float min_hp_ratio_ = 0.5f;
	UPROPERTY(EditDefaultsOnly)
	float max_hp_ratio_ = 0.2f;

	UPROPERTY(EditDefaultsOnly)
	float min_dodge_rate_ = 0.05f;
	UPROPERTY(EditDefaultsOnly)
	float max_dodge_rate_ = 0.15f;

	FBuffStatusData dodge_status_ = {ECharacterStatType::EvasionRate, 0.f, false, true};
};
