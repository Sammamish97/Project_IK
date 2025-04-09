/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 3.9.2025
Summary : Source file for the rune data asset.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "DataAssets/RuneDataAsset.h"

FRuneSetData URuneDataAsset::GetRuneSetData(ERuneSetType type)
{
	checkf(rune_data_map_.Find(type), TEXT("Can't find Rune Set Type in the Rune data map!"));
	return rune_data_map_[type];
}
