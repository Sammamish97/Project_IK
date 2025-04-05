/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.1.2025
Summary : Source file for Passive Skill Data Asset.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "DataAssets/PassiveSkillDataAsset.h"

FPassiveSkillData UPassiveSkillDataAsset::GetPassiveSkillData(EPassiveSkillType type)
{
	checkf(passive_skill_data_map_.Find(type), TEXT("Can't find Passive Type in the passive skill data map!"));
	return passive_skill_data_map_[type];
}
