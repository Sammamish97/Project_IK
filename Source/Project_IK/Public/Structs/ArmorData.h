/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.1.2025
Summary : Header file for the ArmorData.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Managers/EnumCluster.h"

#include "ArmorData.generated.h"

USTRUCT(BlueprintType)
struct PROJECT_IK_API FArmorData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ArmorData")
	EArmorType type = EArmorType::Empty;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ArmorData")
	UTexture2D* thumbnail = nullptr;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ArmorData")
	int armor;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ArmorData")
	int hit_point;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ArmorData")
	int evasion_rate;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ArmorData")
	bool has_skill;
};
