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
#include "PassiveSkillData.generated.h"

USTRUCT(BlueprintType)
struct PROJECT_IK_API FPassiveSkillData
{
	GENERATED_BODY();

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PassiveSkillData")
	EPassiveSkillType type = EPassiveSkillType::INVALID;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PassiveSkillData")
	TSubclassOf<class UPassiveSkillBase> passive_skill_class;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PassiveSkillData")
	UTexture2D* thumbnail = nullptr;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "PassiveSkillData")
	FString flavor_text;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OopartData")
	ERarity rarity_;
};
