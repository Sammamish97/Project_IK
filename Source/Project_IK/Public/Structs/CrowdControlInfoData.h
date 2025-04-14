/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 04.14.2025
Summary : Header file for information struct about crowd controls.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Managers/EnumCluster.h"
#include "CrowdControlInfoData.generated.h"

class UTexture2D;

USTRUCT(BlueprintType)
struct FCrowdControlInfoData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* texture_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ECCType cc_type_;
};