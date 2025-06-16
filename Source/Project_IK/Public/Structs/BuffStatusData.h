/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 03.29.2025
Summary : Header file for the buff data applied to units.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Managers/EnumCluster.h"
#include "BuffStatusData.generated.h"

USTRUCT(BlueprintType)
struct FBuffStatusData
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Buff")
	ECharacterStatType stat_type_;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Buff")
	float value_;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Buff")
	bool is_percentage_;
};