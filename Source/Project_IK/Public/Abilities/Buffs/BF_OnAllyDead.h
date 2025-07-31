/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.31.2025
Summary : Header file for one Ally Dead buff/Debuff.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "BuffHandler.h"
#include "BF_OnAllyDead.generated.h"

UCLASS()
class PROJECT_IK_API UBF_OnAllyDead : public UBuffHandler
{
	GENERATED_BODY()
public:
	virtual void ApplyBuff(AUnit* target) override;

private:
	UFUNCTION()
	void OnAllyDie();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AUnit> ally_class;

	UPROPERTY(EditDefaultsOnly)
	float atk_power_buff_per_ally_die_;

	UPROPERTY(EditDefaultsOnly)
	float atk_speed_buff_per_ally_die_;

	int32 dead_ally_ = 0;

	UPROPERTY(Transient)
	TWeakObjectPtr<AUnit> target_cache_;
};