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

USTRUCT()
struct PROJECT_IK_API FRuneData
{
	GENERATED_BODY();

	UPROPERTY()
	TObjectPtr<UTexture2D> thumbnail;

	//1, 2, 3, 4, 5, 6번 슬롯을 뜻함.
	UPROPERTY()
	uint8 slot_type = 0;
	
	UPROPERTY()
	ERuneSetType set_type = ERuneSetType::INVALID;

	UPROPERTY()
	FStatusData rune_status = FStatusData();
};