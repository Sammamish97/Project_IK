/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 2.3.2025
Summary : Header file for Perk nodes.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Managers/EnumCluster.h"
#include "PerkNode.generated.h"


enum class ECharacterStatType : uint8;

USTRUCT(BlueprintType)
struct FPerkNode
{
	GENERATED_BODY()
public:

	UPROPERTY(VisibleAnywhere, Category = "PerkData")
	ECharacterStatType stat_;

	UPROPERTY(VisibleAnywhere, Category = "PerkData")
	float modifier_;	

	UPROPERTY(VisibleAnywhere, Category = "PerkData")
	int32 cost_;

	UPROPERTY(VisibleAnywhere, Category = "PerkData")
	TArray<int32> next_;
};