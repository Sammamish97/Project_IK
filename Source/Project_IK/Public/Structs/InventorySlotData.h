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
	bool is_empty = true;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "inventory slot data")
	EGearType gear_type;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "inventory slot data")
	EArmorType armor_type;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "inventory slot data")
	ETrinketType trinket_type;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "inventory slot data")
	EWeaponType weapon_type;

	//TODO: OopartType, ActiveType, PassiveType이 추가되어야 함.
};
