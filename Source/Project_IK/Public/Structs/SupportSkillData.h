/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.02.2025
Summary : Header file for the Weapon status data structure.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Managers/EnumCluster.h"
#include "SupportSkillData.generated.h"

USTRUCT(BlueprintType)
struct PROJECT_IK_API FSupportSkillData
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "SupportSkillData")
	ESupportSkillType type_ = ESupportSkillType::INVALID;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TSubclassOf<class USupportSkillBase> support_skill_class_;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "SupportSkillData")
	TObjectPtr<UTexture2D> thumbnail = nullptr;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "SupportSkillData")
	FString flavor_text;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "SupportSkillData")
	ERarity rarity_;
};
