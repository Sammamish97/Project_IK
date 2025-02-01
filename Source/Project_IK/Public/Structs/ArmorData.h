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
	EArmorType type_ = EArmorType::Empty;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ArmorData")
	UTexture2D* thumbnail_ = nullptr;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ArmorData")
	int armor_;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ArmorData")
	int health_;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ArmorData")
	int evasion_rate_;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ArmorData")
	bool has_skill_;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "ArmorData")
	int skill_index_;
};
