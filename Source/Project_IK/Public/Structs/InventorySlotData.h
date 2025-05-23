/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.06.2025
Summary : Header file for inventory slot data structure.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Managers/EnumCluster.h"
#include "InventorySlotData.generated.h"

USTRUCT(BlueprintType)
struct PROJECT_IK_API FInventorySlotData
{
	GENERATED_BODY();
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "inventory slot data")
	EGearType gear_type = EGearType::INVALID;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "inventory slot data")
	EWeaponType weapon_type = EWeaponType::INVALID;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "inventory slot data")
	EPassiveSkillType passive_skill_type = EPassiveSkillType::INVALID;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "inventory slot data")
	EActiveSkillType active_skill_type = EActiveSkillType::INVALID;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "inventory slot data")
	bool is_empty = true;
};
