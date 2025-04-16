/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 04.14.2025
Summary : Source file for data assets for status information.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "DataAssets/StatInfoDataAsset.h"

UTexture2D* UStatInfoDataAsset::GetStatTexture(ECharacterStatType stat_type)
{
	checkf(stat_info_data_map_.Find(stat_type), TEXT("Can't find stat type in the stat info data map!"));
	return stat_info_data_map_[stat_type].texture_;
}
