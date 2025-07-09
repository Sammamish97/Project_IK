/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 3.24.2025
Summary : Struct file for Targeting Parameters.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Managers/EnumCluster.h"
#include "TargetParameters.generated.h"

USTRUCT(BlueprintType)
struct PROJECT_IK_API FTargetParameters
{
	GENERATED_BODY()
	
	FTargetParameters(ETargetingMode mode = ETargetingMode::None, ETargetType type = ETargetType::All, float range = 0.f, float radius = 0.f, bool is_self_targeting = false)
		: current_mode_(mode), target_type_(type), range_(range), radius_(radius), is_self_targeting_(is_self_targeting)
	{	}

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Targeting")
	ETargetingMode current_mode_;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Targeting")
	ETargetType target_type_;

	// How far selectable
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Targeting")
	float range_;

	// A radius of selected area, an arc width in 360degree for direction mode 
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Targeting")
	float radius_;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Targeting")
	bool is_self_targeting_;
};
