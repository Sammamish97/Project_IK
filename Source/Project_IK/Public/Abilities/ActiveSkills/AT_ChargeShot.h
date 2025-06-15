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

UCLASS()
class PROJECT_IK_API UAT_ChargeShot : public UActiveSkillBase
{
	GENERATED_BODY()
	
public:
	UAT_ChargeShot();
	virtual TOptional<FTargetParameters> ActivateSkill(const FTargetResult& TargetResult) override;
	void OnChargeShot(AActor* target, class UWeaponMechanics* OtherTarget, FDamageData dmg_data);

private:
	float charge_time_ = 1.0f;
	float dmg_scale_ = 1.5f;
	float recoil_time_ = 1.0f;
};
