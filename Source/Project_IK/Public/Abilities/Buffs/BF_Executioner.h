/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.28.2025
Summary : Header file for the Executioner passive skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "BuffHandler.h"
#include "Structs/BuffStatusData.h"
#include "BF_Executioner.generated.h"

UCLASS()
class PROJECT_IK_API UBF_Executioner : public UBuffHandler
{
	GENERATED_BODY()
public:
	virtual void ApplyBuff(AUnit* target) override;

private:
	UFUNCTION()
	void OnEliminate();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Buffs", meta = (AllowPrivateAccess = "true"))
	FBuffStatusData buff_status_data_;

	UPROPERTY(Transient)
	TWeakObjectPtr<AUnit> target_cache_;
};
