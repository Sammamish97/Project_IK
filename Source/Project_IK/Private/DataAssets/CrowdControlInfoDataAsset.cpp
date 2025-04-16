/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 04.14.2025
Summary : Source file for data assets for CC information.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "DataAssets/CrowdControlInfoDataAsset.h"



UTexture2D* UCrowdControlInfoDataAsset::GetCCTexture(ECCType cc_type)
{
	checkf(cc_info_data_map_.Find(cc_type), TEXT("Can't find stat type in the stat info data map!"));
	return cc_info_data_map_[cc_type].texture_;
}
