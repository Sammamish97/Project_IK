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
#include "RuneSetData.generated.h"

USTRUCT(BlueprintType)
struct PROJECT_IK_API FRuneSetData
{
	GENERATED_BODY()

	void Init()
	{
		for (auto& elem : rune_set_data_)
		{
			elem.thumbnail_ = thumbnail_;
			elem.set_type = set_type;
		}
	}
	
	UPROPERTY(EditFixedSize)
	TArray<FRuneData> rune_set_data_ = { FRuneData(0), FRuneData(1), FRuneData(2), FRuneData(3), FRuneData(4), FRuneData(5) };

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	TObjectPtr<UTexture2D> thumbnail_;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	ERuneSetType set_type = ERuneSetType::INVALID;

	UPROPERTY(EditDefaultsOnly)
	ERarity rarity_;
};
