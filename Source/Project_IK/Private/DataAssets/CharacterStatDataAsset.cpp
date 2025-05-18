/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 05.04.2025
Summary : Source file for data assets for character stats.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "DataAssets/CharacterStatDataAsset.h"

const FCharacterData& UCharacterStatDataAsset::GetCharacterData(ECharacterType unit_type)
{
	checkf(character_data_map_.Find(unit_type), TEXT("Can't find stat type in the stat info data map!"));
	return character_data_map_[unit_type];
}

void UCharacterStatDataAsset::EnhanceCharacterData(ECharacterType unit_type, ECharacterStatType stat_type, float increase_amount)
{
	checkf(character_data_map_.Find(unit_type), TEXT("Can't find stat type in the stat info data map!"));
	character_data_map_[unit_type].status_data_[stat_type] += increase_amount;
}

void UCharacterStatDataAsset::DiminishCharacterData(ECharacterType unit_type, ECharacterStatType stat_type, float decrease_amount)
{
	checkf(character_data_map_.Find(unit_type), TEXT("Can't find stat type in the stat info data map!"));
	character_data_map_[unit_type].status_data_[stat_type] -= decrease_amount;
}
