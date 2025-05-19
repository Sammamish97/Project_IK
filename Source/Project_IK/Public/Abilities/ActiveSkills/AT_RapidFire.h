/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.15.2025
Summary : Header file for Rapid Fire Active Skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Abilities/SkillBase.h"
#include "AT_RapidFire.generated.h"

UCLASS()
class PROJECT_IK_API UAT_RapidFire : public USkillBase
{
	GENERATED_BODY()
public:
	UAT_RapidFire();
	virtual bool ActivateSkill_Implementation(const FTargetResult& TargetResult) override;

private:
	virtual void OnRapidFire(AActor* target, class UWeaponMechanics* weapon_mechanics_cache, FDamageData dmg_data, float attack_speed);

private:
	float attack_speed_increase_amount_ = 3.f;
	float accuracy_rand_range = 200.f;
};

