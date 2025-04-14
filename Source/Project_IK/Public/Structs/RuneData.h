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
#include "StatusData.h"
#include "Managers/EnumCluster.h"
#include "RuneData.generated.h"

USTRUCT(BlueprintType)
struct PROJECT_IK_API FRuneData
{
	GENERATED_BODY();

public:
	FRuneData(int32 init_slot = 0, bool is_empty = true, ERuneSetType init_set_type = ERuneSetType::INVALID, FStatusData init_status = FStatusData())
	: set_type(init_set_type),rune_status(init_status), slot_number(init_slot){};
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "RuneData")
	ERuneSetType set_type = ERuneSetType::INVALID;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "RuneData")
	FStatusData rune_status = FStatusData();

	//0, 1, 2, 3, 4, 5번 슬롯을 뜻함.
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "RuneData")
	int32 slot_number = 0;
};