/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.09.2025
Summary : Structure for Active Skill data.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "ItemData.h"
#include "Managers/EnumCluster.h"
#include "ActiveSkillData.generated.h"
USTRUCT(BlueprintType)
struct PROJECT_IK_API FActiveSkillData
{
	GENERATED_BODY();
	UPROPERTY(EditDefaultsOnly)
	EActiveSkillType type_ = EActiveSkillType::INVALID;
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UActiveSkillBase> active_skill_class;

	UPROPERTY(EditDefaultsOnly)
	FItemData item_data_;

	UPROPERTY(EditDefaultsOnly)
	float skill_power_ratio_;
};
