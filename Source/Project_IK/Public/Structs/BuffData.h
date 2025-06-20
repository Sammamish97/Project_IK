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
#include "UObject/Object.h"
#include "BuffData.generated.h"

USTRUCT(BlueprintType)
struct PROJECT_IK_API FBuffData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ActiveSkillData")
	FText buff_name_;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ActiveSkillData")
	EBuffType buff_type_ = EBuffType::INVALID;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ActiveSkillData")
	UTexture2D* thumbnail = nullptr;

	UPROPERTY( BlueprintReadWrite, EditDefaultsOnly,Category = "Buff")
	float duration_ = 0.f;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Buff")
	bool is_permanent_ = false;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Buff")
	FString detail_;
	
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "ActiveSkillData")
	TArray<FBuffStatusData> buff_status_;
};