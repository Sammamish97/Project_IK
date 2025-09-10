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
#include "WeaponStatusData.h"
#include "Managers/EnumCluster.h"
#include "WeaponData.generated.h"

USTRUCT(BlueprintType)
struct PROJECT_IK_API FWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AGunBase> weapon_class_ = nullptr;
	
	UPROPERTY(EditDefaultsOnly)
	EWeaponType type_ = EWeaponType::INVALID;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UTexture2D> thumbnail_ = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FWeaponStatusData status_data_;

	UPROPERTY(EditDefaultsOnly)
	ERarity rarity_;
};