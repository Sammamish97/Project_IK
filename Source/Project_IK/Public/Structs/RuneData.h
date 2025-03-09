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
	FRuneData() = default;
	FRuneData(uint8 init_slot, ERuneSetType init_set_type = ERuneSetType::INVALID, FStatusData init_status = FStatusData())
	: slot_number(init_slot), set_type(init_set_type),rune_status(init_status) {};

	UPROPERTY()
	TObjectPtr<UTexture2D> thumbnail;

	//0, 1, 2, 3, 4, 5번 슬롯을 뜻함.
	UPROPERTY(BlueprintReadOnly, VisibleDefaultsOnly, Category = "RuneData")
	uint8 slot_number = 0;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "RuneData")
	ERuneSetType set_type = ERuneSetType::INVALID;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "RuneData")
	FStatusData rune_status = FStatusData();
};