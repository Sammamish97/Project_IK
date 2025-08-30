/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 04.04.2025
Summary : Header file for Event Data Struct.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Managers/EnumCluster.h"
#include "EventData.generated.h"

USTRUCT(BlueprintType)
struct PROJECT_IK_API FEventData
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "EventData")
	TObjectPtr<UTexture2D> situation_;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "EventData")
	EEventType event_type_;
};
