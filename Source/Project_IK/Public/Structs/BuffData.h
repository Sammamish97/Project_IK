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
#include "BuffData.generated.h"

USTRUCT(BlueprintType)
struct FBuffData
{
public:
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Buff")
	FName buff_name_;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Buff")
	ECharacterStatType  stat_type_;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Buff")
	float value_;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Buff")
	bool is_percentage_;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Buff")
	bool is_permanent_;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Buff")
	float duration_;

	UPROPERTY(VisibleAnywhere, Transient, BlueprintReadOnly, Category = "Buff")
	float time_remaining_;



	FBuffData()
		: stat_type_(ECharacterStatType::AttackPower), value_(0.f), is_percentage_(false), is_permanent_(false), duration_(0.f), time_remaining_(0.f)
	{}

	FBuffData(FName Name, ECharacterStatType StatType, float Value, bool IsPercentage, float Duration)
		: buff_name_(Name), stat_type_(StatType), value_(Value), is_percentage_(IsPercentage), is_permanent_(false), duration_(Duration), time_remaining_(Duration)
	{}

	FBuffData(FName Name, ECharacterStatType StatType, float Value, bool IsPercentage, bool IsPermanent)
		: buff_name_(Name), stat_type_(StatType), value_(Value), is_percentage_(IsPercentage), is_permanent_(true), duration_(0.f), time_remaining_(0.f)
	{}
};