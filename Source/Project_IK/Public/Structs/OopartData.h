/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.18.2025
Summary : Structure for Oopart.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Managers/EnumCluster.h"
#include "OopartData.generated.h"

USTRUCT(BlueprintType)
struct PROJECT_IK_API FOopartData : public FTableRowBase
{
	GENERATED_BODY();
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "OopartData")
	EOopartType type = EOopartType::Empty;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "OopartData")
	TSubclassOf<class AOopartBase> oopart_class;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "OopartData")
	UTexture2D* thumbnail = nullptr;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "OopartData")
	FString flavor_text;
};
