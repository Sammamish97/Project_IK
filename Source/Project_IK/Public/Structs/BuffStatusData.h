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

	FBuffStatusData(ECharacterStatType stat_type, float value, bool is_percentage, bool is_permanent = false, float duration = 0.f)
		: stat_type_(stat_type), value_(value), is_percentage_(is_percentage), is_permanent_(is_permanent), duration_(duration)
	{
	}	
	
	// Rule of Five:
	FBuffStatusData() = default;
	FBuffStatusData(const FBuffStatusData& other) = default;            // Copy constructor
	FBuffStatusData(FBuffStatusData&& other) noexcept = default;        // Move constructor
	FBuffStatusData& operator=(const FBuffStatusData& other) = default; // Copy assignment
	FBuffStatusData& operator=(FBuffStatusData&& other) noexcept = default; // Move assignment
	~FBuffStatusData() = default;                                       // Destructor

	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Buff")
	ECharacterStatType stat_type_;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Buff")
	float value_;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Buff")
	bool is_percentage_;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Buff")
	bool is_permanent_ = false;
	
	UPROPERTY( BlueprintReadWrite, EditDefaultsOnly,Category = "Buff")
	float duration_ = 0.f;
};