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
#include "Managers/RandomDataAssetsManager.h"

FSupportSkillData USupportSkillDataAsset::GetSupportSkillData(ESupportSkillType type)
{
	checkf(support_skill_data_map_.Find(type), TEXT("Can't find stat type in the stat info data map!"));
	return support_skill_data_map_[type];
}

FSupportSkillData USupportSkillDataAsset::GetSupportSkillDataRandomly(ERarity weight_rarity)
{
	return URandomDataAssetsManager::GetDataAssetRandomly(weight_rarity, support_skill_data_map_);
}

TArray<FSupportSkillData> USupportSkillDataAsset::GetUniqueSupportSkillDataRandomly(int32 n, ERarity weight_rarity)
{
	return URandomDataAssetsManager::GetUniqueDataAssetsRandomly(n, weight_rarity, support_skill_data_map_);
}
