/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.02.2025
Summary : Header file for the skill data structure.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Managers/EnumCluster.h"
#include "ItemData.generated.h"

USTRUCT(BlueprintType)
struct PROJECT_IK_API FItemData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ActiveSkillData")
	UTexture2D* thumbnail = nullptr;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ActiveSkillData")
	FText name_;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ActiveSkillData")
	FText detail_;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "SupportSkillData")
    FText flavor_text;
    
    UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "SupportSkillData")
    ERarity rarity_;
};
