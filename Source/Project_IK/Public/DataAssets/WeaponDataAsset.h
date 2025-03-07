/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 3.7.2025
Summary : Header file for WeaponDataAsset.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Managers/EnumCluster.h"
#include "Structs/WeaponData.h"
#include "WeaponDataAsset.generated.h"

UCLASS()
class PROJECT_IK_API UWeaponDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Data")
	TMap<EWeaponType, FWeaponData> weapon_data_map_;
};
