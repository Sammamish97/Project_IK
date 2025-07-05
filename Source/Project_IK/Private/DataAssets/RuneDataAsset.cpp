/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 3.9.2025
Summary : Source file for the rune data asset.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "DataAssets/RuneDataAsset.h"

#include "Managers/RandomDataAssetsManager.h"

FRuneSetData URuneDataAsset::GetRuneSetData(ERuneSetType type)
{
	checkf(rune_data_map_.Find(type), TEXT("Can't find Rune Set Type in the Rune data map!"));
	return rune_data_map_[type];
}

FRuneSetData URuneDataAsset::GetRuneSetDataRandomly(ERarity weight_rarity)
{
	return URandomDataAssetsManager::GetDataAssetRandomly(weight_rarity, rune_data_map_);
}

TArray<FRuneSetData> URuneDataAsset::GetRuneSetDataRandomly(int32 n, ERarity weight_rarity)
{
	return URandomDataAssetsManager::GetDataAssetRandomly(n, weight_rarity, rune_data_map_);
}

TArray<FRuneSetData> URuneDataAsset::GetUniqueRuneSetDataRandomly(int32 n, ERarity weight_rarity)
{
	return URandomDataAssetsManager::GetUniqueDataAssetsRandomly(n, weight_rarity, rune_data_map_);
}

FText URuneDataAsset::GetRuneSetBonusDetail(ERuneSetType set_type, ERuneBonusType bonus_type)
{
	return rune_data_map_[set_type].bonus_details_[bonus_type];
}
