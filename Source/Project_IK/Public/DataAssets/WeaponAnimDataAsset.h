/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.15.2025
Summary : Header file for the Weapon Anim Data Asset.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Managers/EnumCluster.h"
#include "Structs/UnitWeaponAnimMap.h"
#include "WeaponAnimDataAsset.generated.h"

UCLASS()
class PROJECT_IK_API UWeaponAnimDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	TSoftObjectPtr<UAnimMontage> GetUnitWeaponAnimData(EUnitBoneType bone, EWeaponAnimationType weapon, EWeaponAction action);
	TSoftObjectPtr<UAnimBlueprint> GetUnitWeaponAnimInstance(EUnitBoneType bone, EWeaponAnimationType weapon);

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon Anim Data", meta = (AllowPrivateAccess = "true"))
	TMap<EUnitBoneType, FUnitWeaponAnimMap> unit_weapon_anim_map_;
};
