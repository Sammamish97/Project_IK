/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.5.2025
Summary : Header file for Reward Data.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "ActiveSkillData.h"
#include "PassiveSkillData.h"
#include "RuneData.h"
#include "WeaponData.h"
#include "UObject/Object.h"
#include "RewardData.generated.h"

USTRUCT()
struct PROJECT_IK_API FRewardData
{
	GENERATED_BODY()

	EGearType gear_type_;

	FWeaponData weapon_data_;
	FActiveSkillData active_skill_data_;
	FPassiveSkillData passive_skill_data_;
	FRuneData rune_data_;
};