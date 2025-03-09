/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 3.9.2025
Summary : Header file for the rune set data asset.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Structs/RuneData.h"
#include "RuneSetDataAsset.generated.h"

UCLASS()
class PROJECT_IK_API URuneSetDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon Data", EditFixedSize)
	TArray<FRuneData> rune_set_data_ = { FRuneData(0), FRuneData(1), FRuneData(2), FRuneData(3), FRuneData(4), FRuneData(5) };
};
