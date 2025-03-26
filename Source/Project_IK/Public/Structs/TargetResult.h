/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 3.24.2025
Summary : Struct file for Targeting Result.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "TargetParameters.h"
#include "TargetResult.generated.h"

USTRUCT(BlueprintType)
struct PROJECT_IK_API FTargetResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Targeting")
	TArray<TObjectPtr<AActor>> target_actors_ = TArray<TObjectPtr<AActor>>();

	UPROPERTY(BlueprintReadWrite, Category = "Targeting")
	FVector target_location_ = FVector::ZeroVector;

	UPROPERTY(BlueprintReadWrite, Category = "Targeting")
	FRotator target_rotation_ = FRotator::ZeroRotator;

	UPROPERTY(BlueprintReadWrite, Category = "Targeting")
	FTargetParameters target_parameters_;
};
