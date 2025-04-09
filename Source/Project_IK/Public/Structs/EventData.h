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
struct PROJECT_IK_API FEventData : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "RuneData")
	TObjectPtr<UTexture2D> situation_;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "RuneData")
	EEventType event_type_;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "RuneData")
	FText event_title_;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "RuneData")
	FText text_body_;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "RuneData")
	FText option_1;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "RuneData")
	FText option_2;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "RuneData")
	FText option_3;
};
