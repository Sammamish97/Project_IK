/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.22.2025
Summary : Source file for the Support SKill Data Asset.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "DataAssets/SupportSkillDataAsset.h"
#include "Abilities/SupportSkills/SupportSkillBase.h"

TSubclassOf<USupportSkillBase> USupportSkillDataAsset::GetSupportSkillClass(ESupportSkillType type)
{
	checkf(support_skill_data_map_.Find(type), TEXT("Can't find stat type in the stat info data map!"));
	return support_skill_data_map_[type];
}