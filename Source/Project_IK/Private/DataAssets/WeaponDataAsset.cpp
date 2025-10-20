/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 3.7.2025
Summary : Source file for WeaponDataAsset.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "DataAssets/WeaponDataAsset.h"

#include "Managers/RandomDataAssetsManager.h"

FWeaponData UWeaponDataAsset::GetWeaponData(EWeaponType type)
{
	checkf(weapon_data_map_.Find(type), TEXT("Can't find Weapon Type in the Weapon data map!"));
	return weapon_data_map_[type];
}

FWeaponData UWeaponDataAsset::GetWeaponDataRandomly(UWorld* world, ERarity weight_rarity)
{
	return URandomDataAssetsManager::GetDataAssetRandomly(weight_rarity, weapon_data_map_, world);
}

FWeaponData UWeaponDataAsset::GetWeaponDataByRarity(UWorld* world, ERarity rarity)
{
	return URandomDataAssetsManager::GetDataAssetByRarity(rarity, weapon_data_map_, world);
}

TArray<FWeaponData> UWeaponDataAsset::GetUniqueWeaponDataRandomly(int32 n, UWorld* world, ERarity weight_rarity)
{
	return URandomDataAssetsManager::GetUniqueDataAssetsRandomly(n, weight_rarity, weapon_data_map_, world);
}
