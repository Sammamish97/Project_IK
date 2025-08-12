/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.13.2025
Summary : Header file for perk connection color.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PerkConnectionColor.generated.h"

USTRUCT()
struct PROJECT_IK_API FPerkConnectionColor
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	FLinearColor default_color_;

	UPROPERTY(EditAnywhere)
	float max_default_opacity_;

	UPROPERTY(EditAnywhere)
	FLinearColor purchased_;

	UPROPERTY(EditAnywhere)
	float max_purchased_opacity_;
};
