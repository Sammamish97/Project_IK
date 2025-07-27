/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.22.2025
Summary : Header file for Display Data Asset.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Structs/FormattedText.h"
#include "DisplayDataAsset.generated.h"

UCLASS()
class PROJECT_IK_API UDisplayDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "DisplayData")
	TObjectPtr<UTexture2D> thumbnail = nullptr;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "DisplayData")
	FText name_;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "DisplayData")
	FFormattedText detail_;
};
