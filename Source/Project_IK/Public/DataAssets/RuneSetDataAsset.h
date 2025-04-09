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
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "RuneSet")
	TObjectPtr<UTexture2D> thumbnail;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RuneSet", EditFixedSize)
	TArray<FRuneData> rune_set_data_ = { FRuneData(0, false), FRuneData(1, false), FRuneData(2, false), FRuneData(3, false), FRuneData(4, false), FRuneData(5, false) };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RuneSet")
	ERarity rarity_;
};
