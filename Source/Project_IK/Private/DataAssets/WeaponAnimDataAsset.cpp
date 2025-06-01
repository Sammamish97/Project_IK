/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.15.2025
Summary : Source file for the Weapon Anim Data Asset.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "DataAssets/WeaponAnimDataAsset.h"

TSoftObjectPtr<UAnimMontage> UWeaponAnimDataAsset::GetUnitWeaponAnimData(EUnitBoneType bone,
	EWeaponAnimationType weapon, EWeaponAction action)
{
	checkf(unit_weapon_anim_map_.Find(bone), TEXT("Can't find Bone Type in the Weapon data map!"));
	return unit_weapon_anim_map_[bone].GetWeaponAnimData(weapon, action);
}

TSoftObjectPtr<UAnimBlueprint> UWeaponAnimDataAsset::GetUnitWeaponAnimInstance(EUnitBoneType bone,
	EWeaponAnimationType weapon)
{
	checkf(unit_weapon_anim_map_.Find(bone), TEXT("Can't find Bone Type in the Weapon data map!"));
	return unit_weapon_anim_map_[bone].GetWeaponAnimInstance(weapon);
}
