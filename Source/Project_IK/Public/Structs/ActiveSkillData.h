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
#include "Managers/EnumCluster.h"
#include "ActiveSkillData.generated.h"

USTRUCT(BlueprintType)
struct PROJECT_IK_API FActiveSkillData : public FTableRowBase
{
	GENERATED_BODY();
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ActiveSkillData")
	EActiveSkillType type;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ActiveSkillData")
	TSubclassOf<class UActiveSkillBase> active_skill_class;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ActiveSkillData")
	UTexture2D* thumbnail = nullptr;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ActiveSkillData")
	FString flavor_text;
};
