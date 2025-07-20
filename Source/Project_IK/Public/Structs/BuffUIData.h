/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 06.20.2025
Summary : Header file for Event Data Struct.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "BuffStatusData.h"
#include "ItemData.h"
#include "UObject/Object.h"
#include "BuffUIData.generated.h"

USTRUCT(BlueprintType)
struct PROJECT_IK_API FBuffUIData
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Buff")
	FItemData item_data_;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ActiveSkillData")
	EBuffType buff_type_ = EBuffType::INVALID;

	UPROPERTY( BlueprintReadWrite, EditDefaultsOnly,Category = "Buff")
	float duration_ = 0.f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Buff")
	bool is_permanent_ = false;
};