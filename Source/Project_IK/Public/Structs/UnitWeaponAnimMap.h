/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.15.2025
Summary : Header file for the Unit Weapon Anim Map.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "WeaponAnimStruct.h"
#include "Managers/EnumCluster.h"
#include "UnitWeaponAnimMap.generated.h"

USTRUCT(BlueprintType)
struct PROJECT_IK_API FUnitWeaponAnimMap
{
	GENERATED_BODY()

public:
	TSoftObjectPtr<UAnimMontage> GetWeaponAnimData(EWeaponAnimationType weapon, EWeaponAction action)
	{
		checkf(weapon_anim_map_.Find(weapon), TEXT("Can't find Weapon Type in the Weapon data map!"));
		return weapon_anim_map_[weapon][action];
	}

	TSoftObjectPtr<UAnimBlueprint> GetWeaponAnimInstance(EWeaponAnimationType weapon)
	{
		return weapon_anim_map_[weapon].weapon_anim_instance_;
	}
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Anim Data", meta = (AllowPrivateAccess = "true"))
	TMap<EWeaponAnimationType, FWeaponAnimStruct> weapon_anim_map_;
};