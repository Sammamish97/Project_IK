/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.19.2025
Summary : Source file for Buff Data Asset.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "DataAssets/BuffUIDataAsset.h"

FBuffUIData UBuffUIDataAsset::GetBuffUIData(EBuffType type)
{
	return buff_UI_data_[type];
}
