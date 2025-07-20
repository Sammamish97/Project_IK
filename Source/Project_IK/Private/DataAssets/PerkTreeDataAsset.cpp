/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 07.13.2025
Summary : Source file for data assets for perk tree.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "DataAssets/PerkTreeDataAsset.h"

const TArray<FPerkNode>& UPerkTreeDataAsset::GetTree() const
{
	return tree_;
}
