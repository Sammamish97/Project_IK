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
struct PROJECT_IK_API FPassiveSkillData : public FTableRowBase
{
	GENERATED_BODY();
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponData")
	EPassiveSkillType type;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponData")
	TSubclassOf<class UEquipSkillBase> passive_skill_class;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponData")
	UTexture2D* thumbnail = nullptr;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponData")
	FString flavor_text;
};
