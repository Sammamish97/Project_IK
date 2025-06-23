/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.1.2025
Summary : Header file for the DamageData.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Managers/EnumCluster.h"
#include "DamageData.generated.h"

USTRUCT(BlueprintType)
struct PROJECT_IK_API FDamageData
{
GENERATED_BODY()

public:
	FDamageData(float atk_base_dmg = 0.f, float skill_power_base_dmg = 0.f, EDamageType damage_type = EDamageType::INVALID, TWeakObjectPtr<AActor> attacker = nullptr, TWeakObjectPtr<AActor> attack_target = nullptr, bool is_critical_shot = false)
		: atk_base_dmg_(atk_base_dmg), skill_power_base_dmg_(skill_power_base_dmg), damage_type_(damage_type), attacker_(attacker), attack_target_(attack_target), is_critical_shot_(is_critical_shot)
	{}

	UPROPERTY(Transient)
	float atk_base_dmg_ = 0;

	UPROPERTY(Transient)
	float skill_power_base_dmg_ = 0;

	UPROPERTY(Transient)
	EDamageType damage_type_ = EDamageType::INVALID;

	UPROPERTY(Transient)
	TWeakObjectPtr<AActor> attacker_ = nullptr;
	
	UPROPERTY(Transient)
	TWeakObjectPtr<AActor> attack_target_ = nullptr;

	UPROPERTY(Transient)
	bool is_critical_shot_ = false;
};
