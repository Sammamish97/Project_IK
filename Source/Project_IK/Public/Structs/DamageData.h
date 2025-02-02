/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.1.2025
Summary : Header file for the DamageData.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Managers/EnumCluster.h"
#include "DamageData.generated.h"

USTRUCT(BlueprintType)
struct PROJECT_IK_API FDamageData
{
GENERATED_BODY()
	float damage;
	EDamageType damage_type;
	TWeakObjectPtr<AActor> attacker;
	//다음의 정보도 사용될 가능성이 있다.
	//FVector hit_pos_;
};
