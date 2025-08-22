/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.1.2025
Summary : Source file for Active Skill Data Asset.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "DataAssets/ActiveSkillDataAsset.h"

#include "Managers/RandomDataAssetsManager.h"

FActiveSkillData UActiveSkillDataAsset::GetActiveSkillData(EActiveSkillType type)
{
	checkf(active_skill_data_map_.Find(type), TEXT("Can't find Active Skill Type in the active skill data map!"));
	return active_skill_data_map_[type];	
}

FActiveSkillData UActiveSkillDataAsset::GetActiveSkillDataRandomly(ERarity weight_rarity)
{
	return URandomDataAssetsManager::GetDataAssetRandomly(weight_rarity, active_skill_data_map_);
}

FActiveSkillData UActiveSkillDataAsset::GetActiveSkillDataByRarity(ERarity rarity)
{
	return URandomDataAssetsManager::GetDataAssetByRarity(rarity, active_skill_data_map_);
}

TArray<FActiveSkillData> UActiveSkillDataAsset::GetUniqueActiveSkillDataRandomly(int32 n, ERarity weight_rarity)
{
	return URandomDataAssetsManager::GetUniqueDataAssetsRandomly(n, weight_rarity, active_skill_data_map_);
}
