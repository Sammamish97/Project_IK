/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.1.2025
Summary : Source file for Passive Skill Data Asset.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "DataAssets/PassiveSkillDataAsset.h"
#include "Managers/RandomDataAssetsManager.h"

FPassiveSkillData UPassiveSkillDataAsset::GetPassiveSkillData(EPassiveSkillType type)
{
	checkf(passive_skill_data_map_.Find(type), TEXT("Can't find Passive Type in the passive skill data map!"));
	return passive_skill_data_map_[type];
}

FPassiveSkillData UPassiveSkillDataAsset::GetPassiveSkillDataRandomly(ERarity weight_rarity)
{
	return URandomDataAssetsManager::GetDataAssetRandomly(weight_rarity, passive_skill_data_map_);
}

TArray<FPassiveSkillData> UPassiveSkillDataAsset::GetPassiveSkillDataByRarity(int32 n, ERarity rarity)
{
	return URandomDataAssetsManager::GetDataAssetByRarity(n, rarity, passive_skill_data_map_);
}

TArray<FPassiveSkillData> UPassiveSkillDataAsset::GetUniquePassiveSkillDataRandomly(int32 n, ERarity weight_rarity)
{
	return URandomDataAssetsManager::GetUniqueDataAssetsRandomly(n, weight_rarity, passive_skill_data_map_);
}
