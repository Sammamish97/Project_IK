/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.1.2025
Summary : Source file for Oopart Data Asset.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "DataAssets/OopartDataAsset.h"

FOopartData UOopartDataAsset::GetOopartData(EOopartType type)
{
	checkf(oopart_data_map_.Find(type), TEXT("Can't find Oopart Type in the Oopart data map!"));
	return oopart_data_map_[type];
}
