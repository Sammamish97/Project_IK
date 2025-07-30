/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.24.2025
Summary : Header file for one Maintain buff.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "BuffHandler.h"
#include "BF_Maintain.generated.h"

UCLASS()
class PROJECT_IK_API UBF_Maintain : public UBuffHandler
{
	GENERATED_BODY()
public:
	//Shield + Heal
	virtual void ApplyBuff(AUnit* target) override;
	virtual void RemoveBuff(AUnit* target) override;
private:
	virtual void Heal();
	
	UPROPERTY(EditDefaultsOnly, Category = "Buffs", meta = (AllowPrivateAccess = "true"))
	float shield_amount_;
	
	UPROPERTY(EditDefaultsOnly, Category = "Buffs", meta = (AllowPrivateAccess = "true"))
	float heal_per_half_sec_;

	UPROPERTY(Transient)
	TWeakObjectPtr<AUnit> target_cache_;

	FTimerHandle heal_timer_handle_;
};
