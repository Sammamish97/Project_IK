/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.09.2025
Summary : Structure for Passive Skill data.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Managers/EnumCluster.h"
#include "Structs/ItemData.h"
#include "PassiveSkillData.generated.h"

USTRUCT(BlueprintType)
struct PROJECT_IK_API FPassiveSkillData
{
	GENERATED_BODY();

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PassiveSkillData")
	EPassiveSkillType type = EPassiveSkillType::INVALID;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PassiveSkillData")
	TSubclassOf<class UPassiveSkillBase> passive_skill_class;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FItemData item_data_;
};
