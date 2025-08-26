/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.27.2025
Summary : Header file for Hero Data Struct.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "HeroData.generated.h"

USTRUCT()
struct PROJECT_IK_API FHeroData
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	FText name_key_;
	
	UPROPERTY(EditDefaultsOnly)
	FLinearColor widget_color_;
	
	UPROPERTY(EditDefaultsOnly)
	FLinearColor hp_bar_color_;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UTexture2D> portrait_;
};
