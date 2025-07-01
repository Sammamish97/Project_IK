/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 3.8.2025
Summary : Header file for the Rune Data.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Managers/EnumCluster.h"
#include "Structs/ItemData.h"
#include "RuneData.generated.h"

USTRUCT(BlueprintType)
struct PROJECT_IK_API FRuneData
{
	GENERATED_BODY();

	FRuneData(int32 init_slot = 0, ERuneSetType init_set_type = ERuneSetType::INVALID)
	: set_type(init_set_type), slot_number(init_slot){};
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "RuneData")
	ERuneSetType set_type = ERuneSetType::INVALID;
	
	//0, 1, 2, 3, 4, 5번 슬롯을 뜻함.
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "RuneData")
	int32 slot_number = 0;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "RuneData")
	TMap<ECharacterStatType, float> status_map;
};