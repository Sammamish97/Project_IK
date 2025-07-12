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
	bool IsUpgraded() const
	{
		return upgraded_type_ == EActiveSkillType::INVALID;
	}

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ActiveSkillData")
	EActiveSkillType type_ = EActiveSkillType::INVALID;

	//만약 A급 스킬이라면 상위 스킬이 없으므로 INVALID여야 한다.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ActiveSkillData")
	EActiveSkillType upgraded_type_ = EActiveSkillType::INVALID;

	//만약 B급 스킬이라면 하위 스킬이 없으므로 INVALID여야 한다.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ActiveSkillData")
	EActiveSkillType downgraded_type_ = EActiveSkillType::INVALID;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ActiveSkillData")
	TSubclassOf<class UActiveSkillBase> active_skill_class;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FItemData item_data_;
};
