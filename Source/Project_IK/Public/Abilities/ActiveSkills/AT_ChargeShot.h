/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.12.2025
Summary : Header file for Charge Shot Active Skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Abilities/ActiveSkills/ActiveSkillBase.h"
#include "AT_ChargeShot.generated.h"

class AShockJavelin;

UCLASS()
class PROJECT_IK_API UAT_ChargeShot : public UActiveSkillBase
{
	GENERATED_BODY()
	
public:
	UAT_ChargeShot();
	virtual bool ActivateSkill(const FTargetResult& TargetResult) override;

protected:
	UFUNCTION()
	void FireChargeShot();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AShockJavelin> charge_shot_class_;

	FTimerHandle handler_;

	TWeakObjectPtr<AActor> attack_target_;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float charge_time_ = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float dmg_scale_ = 1.5f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float recoil_time_ = 1.0f;
};
