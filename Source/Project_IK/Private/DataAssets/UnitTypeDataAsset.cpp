/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.17.2025
Summary : Source file for the unit type data asset.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "DataAssets/UnitTypeDataAsset.h"
#include "Characters/Unit.h"
TSubclassOf<AUnit> UUnitTypeDataAsset::GetUnitClass(ECharacterType unit_type)
{
	checkf(unit_type_map_.Find(unit_type), TEXT("Can't find Rune Set Type in the Rune data map!"));
	return unit_type_map_[unit_type];
}