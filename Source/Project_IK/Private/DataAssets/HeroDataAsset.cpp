/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.27.2025
Summary : Source file for Hero Data Asset.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "DataAssets/HeroDataAsset.h"

FHeroData UHeroDataAsset::GetHeroData(EHeroType type)
{
	checkf(hero_data_map_.Find(type), TEXT("Can't find Rune Set Type in the Rune data map!"));
	return hero_data_map_[type];
}
