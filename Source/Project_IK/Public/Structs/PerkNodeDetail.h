/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.13.2025
Summary : Header file for perk node detail.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PerkNodeDetail.generated.h"

class UDisplayDataAsset;
class UPerkEffectBase;

USTRUCT()
struct PROJECT_IK_API FPerkNodeDetail
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TObjectPtr<UDisplayDataAsset> display_data_ = nullptr;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UPerkEffectBase> perk_effect_class = nullptr;
	
	UPROPERTY(EditAnywhere)
	int32 cost_;
	
	UPROPERTY(EditAnywhere)
	bool locked_ = false;

	UPROPERTY(EditAnywhere)
	bool purchased_ = false;
};
