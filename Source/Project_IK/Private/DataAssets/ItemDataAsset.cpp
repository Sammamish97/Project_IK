/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 04.02.2025
Summary : Source file for Item data asset.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "DataAssets/ItemDataAsset.h"

FItemData UItemDataAsset::GetItemData(EItemType type)
{
	checkf(item_data_map_.Find(type), TEXT("Can't find Item type in the Item data map!"));
	return item_data_map_[type];
}
