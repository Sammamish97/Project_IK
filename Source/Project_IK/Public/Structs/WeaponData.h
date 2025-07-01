/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.8.2025
Summary : Header file for the Weapon data structure.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Managers/EnumCluster.h"
#include "Structs/ItemData.h"
#include "WeaponData.generated.h"

USTRUCT(BlueprintType)
struct PROJECT_IK_API FWeaponData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponData")
	TSubclassOf<class AGunBase> weapon_class_ = nullptr;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "WeaponData")
	EWeaponType type_ = EWeaponType::INVALID;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	FItemData item_data_;
};