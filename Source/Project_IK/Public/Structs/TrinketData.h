/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.5.2025
Summary : Header file for the trinket data structure.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Managers/EnumCluster.h"
#include "Abilities/EquipSkills/EquipSkillBase.h"
#include "TrinketData.generated.h"

USTRUCT(BlueprintType)
struct PROJECT_IK_API FTrinketData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "TrinketData")
	ETrinketType type = ETrinketType::Empty;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "TrinketData")
	UTexture2D* thumbnail = nullptr;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "TrinketData")
	float attack = 0.f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "TrinketData")
	float attack_speed = 0.f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "TrinketData")
	float crit_rate = 0.f;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "TrinketData")
	bool has_skill = false;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "TrinketData")
	TSubclassOf<UEquipSkillBase> equipment_skill_class = nullptr;
};
