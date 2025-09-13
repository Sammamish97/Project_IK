/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.5.2025
Summary : Header file for the equip manager.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Managers/DataTableManager.h"

#include "DataAssets/ActiveSkillDataAsset.h"
#include "DataAssets/RuneDataAsset.h"
#include "DataAssets/WeaponDataAsset.h"
#include "DataAssets/GlobalBuffDataAsset.h"
#include "DataAssets/PassiveSkillDataAsset.h"
#include "DataAssets/StatInfoDataAsset.h"
#include "DataAssets/CrowdControlInfoDataAsset.h"
#include "DataAssets/CharacterStatDataAsset.h"
#include "DataAssets/HeroDataAsset.h"
#include "DataAssets/UnitTypeDataAsset.h"
#include "DataAssets/WeaponAnimDataAsset.h"
#include "DataAssets/PerkTreeDataAsset.h"
#include "Structs/WrapperEquipmentData.h"
#include "Algo/RandomShuffle.h"


FWeaponData UDataTableManager::GetEnemyWeaponData(EWeaponType type) const
{
	return enemy_weapon_data_asset_->GetWeaponData(type);
}

FWeaponData UDataTableManager::GetHeroWeaponData(EWeaponType type) const
{
	return hero_weapon_data_asset_->GetWeaponData(type);
}

FWeaponData UDataTableManager::GetWeaponDataRandomly(ERarity weight_rarity) const
{
	return hero_weapon_data_asset_->GetWeaponDataRandomly(weight_rarity);
}

FWeaponData UDataTableManager::GetWeaponDataByRarity(ERarity rarity) const
{
	return hero_weapon_data_asset_->GetWeaponDataByRarity(rarity);
}

TArray<FWeaponData> UDataTableManager::GetUniqueWeaponDataRandomly(int32 n, ERarity weight_rarity) const
{
	return hero_weapon_data_asset_->GetUniqueWeaponDataRandomly(n, weight_rarity);
}

FRuneData UDataTableManager::GetRuneData(ERuneSetType type, int slot_num) const
{
	if (slot_num < 0 || slot_num > 5)
	{
		UE_LOG(LogTemp, Error, TEXT("slot_num is out of range"));
		return FRuneData();
	}
	if (rune_data_asset_)
	{
		auto rune_data = rune_data_asset_->GetRuneSetData(type);
		rune_data.slot_number = slot_num;
		return rune_data;
	}
	UE_LOG(LogTemp, Error, TEXT("rune_data_asset_ is invalid!"));
	return FRuneData();
}

FRuneData UDataTableManager::GetRuneDataRandomly(ERarity weight_rarity) const
{
	FRuneData randomly_chosen_set = rune_data_asset_->GetRuneSetDataRandomly(weight_rarity);
	randomly_chosen_set.slot_number = FMath::RandRange(0, 5);
	return randomly_chosen_set;
}

TArray<FRuneData> UDataTableManager::GetRuneDataRandomly(int32 n, ERarity weight_rarity) const
{
	TArray<FRuneData> set_array = rune_data_asset_->GetRuneSetDataRandomly(n, weight_rarity);

	TArray<FRuneData> result;
	for (FRuneData element : set_array)
	{
		element.slot_number = FMath::RandRange(0, 5);
		result.Add(element);
	}
	return result;
}

TArray<FRuneData> UDataTableManager::GetUniqueRuneDataRandomly(int32 n, ERarity weight_rarity) const
{
	TArray<FRuneData> set_array = rune_data_asset_->GetRuneSetDataRandomly(n, weight_rarity);

	TSet<ERuneSetType> data_set;
	for (const FRuneData& data : set_array)
	{
		data_set.Add(data.set_type);
	}

	for (ERuneSetType rune_type : data_set)
	{
		// Shuffle indices 0-5 to ensure random selection without repeating from same set
		// It might caused a crash when there are at least 6 runes.
		TArray<int32> indices = { 0, 1, 2, 3, 4, 5 };
		Algo::RandomShuffle(indices);

		int32 slot_number_index = 0;
		for (FRuneData& rune_data : set_array)
		{
			if (rune_data.set_type == rune_type)
			{
				rune_data.slot_number = indices[slot_number_index];
				slot_number_index += 1;
			}
		}
	}

	return set_array;
}

UTexture2D* UDataTableManager::GetRuneSetThumbnail(ERuneSetType type) const
{
	return rune_data_asset_->GetRuneSetData(type).thumbnail_;
}

FPassiveSkillData UDataTableManager::GetPassiveSkillData(EPassiveSkillType type) const
{
	return passive_skill_data_asset_->GetPassiveSkillData(type);
}

FPassiveSkillData UDataTableManager::GetPassiveSkillDataRandomly(ERarity weight_rarity) const
{
	return passive_skill_data_asset_->GetPassiveSkillDataRandomly(weight_rarity);
}

TArray<FPassiveSkillData> UDataTableManager::GetPassiveSkillDataByRarity(int32 n, ERarity weight_rarity) const
{
	return passive_skill_data_asset_->GetPassiveSkillDataByRarity(n, weight_rarity);
}

TArray<FPassiveSkillData> UDataTableManager::GetUniquePassiveSkillDataRandomly(int32 n, ERarity weight_rarity) const
{
	return passive_skill_data_asset_->GetUniquePassiveSkillDataRandomly(n, weight_rarity);
}

FActiveSkillData UDataTableManager::GetActiveSkillData(EActiveSkillType type) const
{
	return active_skill_data_asset_->GetActiveSkillData(type);
}

FActiveSkillData UDataTableManager::GetActiveSkillDataRandomly(ERarity weight_rarity) const
{
	return active_skill_data_asset_->GetActiveSkillDataRandomly(weight_rarity);
}

FActiveSkillData UDataTableManager::GetActiveSkillDataByRarity(ERarity rarity) const
{
	return active_skill_data_asset_->GetActiveSkillDataByRarity(rarity);
}

TArray<FActiveSkillData> UDataTableManager::GetUniqueActiveSkillDataRandomly(int32 n, ERarity weight_rarity) const
{
	return active_skill_data_asset_->GetUniqueActiveSkillDataRandomly(n, weight_rarity);
}

const FCharacterData& UDataTableManager::GetCharacterData(ECharacterType char_type) const
{
	return character_stat_data_asset_->GetCharacterData(char_type);
}

void UDataTableManager::EnhanceHeroesStatData(ECharacterStatType stat_type, float increase_amount)
{
	character_stat_data_asset_->EnhanceCharacterData(ECharacterType::Hero1, stat_type, increase_amount);
	character_stat_data_asset_->EnhanceCharacterData(ECharacterType::Hero2, stat_type, increase_amount);
	character_stat_data_asset_->EnhanceCharacterData(ECharacterType::Hero3, stat_type, increase_amount);
	character_stat_data_asset_->EnhanceCharacterData(ECharacterType::Hero4, stat_type, increase_amount);
}

void UDataTableManager::DiminishHeroesStatData(ECharacterStatType stat_type, float decrease_amount)
{
	character_stat_data_asset_->DiminishCharacterData(ECharacterType::Hero1, stat_type, decrease_amount);
	character_stat_data_asset_->DiminishCharacterData(ECharacterType::Hero2, stat_type, decrease_amount);
	character_stat_data_asset_->DiminishCharacterData(ECharacterType::Hero3, stat_type, decrease_amount);
	character_stat_data_asset_->DiminishCharacterData(ECharacterType::Hero4, stat_type, decrease_amount);
}

FGlobalBuffData UDataTableManager::GetGlobalBuffData(EGlobalBuffType buff_type) const
{
	FGlobalBuffData* data = global_buff_data_asset_->global_buff_data_assets_.Find(buff_type);
	if (data)
	{
		return *data;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Retreieved invalid global buff data"));
		return FGlobalBuffData();
	}
}

FWrapperEquipmentData UDataTableManager::GetEquipmentDataRandomly(ERarity weight_rarity) const
{
	int32 data_type = FMath::RandRange(0, 99);

	FWrapperEquipmentData result;

	if (data_type <= 12)
	{
		result.weapons_.Add(GetWeaponDataRandomly(weight_rarity));
	}
	else if(data_type <= 24)
	{
		result.active_skills_.Add(GetActiveSkillDataRandomly(weight_rarity));
	}
	else if(data_type <= 46)
	{
		result.passive_skills_.Add(GetPassiveSkillDataRandomly(weight_rarity));
	}
	else
	{
		result.runes_.Add(GetRuneDataRandomly(weight_rarity));
	}

	return result;
}

FWrapperEquipmentData UDataTableManager::GetUniqueEquipmentDataRandomly(int32 n, ERarity weight_rarity) const
{
	TArray<int32> data_counts({ 0, 0, 0, 0 });

	for (int32 i = 0; i < n; i++)
	{
		int32 index = 0;
		int32 probability = FMath::RandRange(0, 99);

		if (probability <= 12)
		{
			index = 0;
		}
		else if (probability <= 24)
		{
			index = 1;
		}
		else if (probability <= 46)
		{
			index = 2;
		}
		else
		{
			index = 3;
		}

		// Increase count by randomly chosen data index
		data_counts[index] += 1;
	}

	FWrapperEquipmentData result;
	result.weapons_ = GetUniqueWeaponDataRandomly(data_counts[0], weight_rarity);
	result.active_skills_ = GetUniqueActiveSkillDataRandomly(data_counts[1], weight_rarity);
	result.passive_skills_ = GetUniquePassiveSkillDataRandomly(data_counts[2], weight_rarity);
	result.runes_ = GetUniqueRuneDataRandomly(data_counts[3], weight_rarity);

	return result;
}

UTexture2D* UDataTableManager::GetStatTexture(ECharacterStatType stat_type)
{
	return stat_info_data_asset_->GetStatTexture(stat_type);
}

UTexture2D* UDataTableManager::GetCCTexture(ECCType cc_type)
{
	return cc_info_data_asset_->GetCCTexture(cc_type);
}

TSoftObjectPtr<UAnimMontage> UDataTableManager::GetUnitWeaponAnimMontage(EUnitBoneType bone, EWeaponAnimationType weapon,
	EWeaponAction action)
{
	return unit_weapon_anim_asset_->GetUnitWeaponAnimData(bone, weapon, action);
}

TSoftObjectPtr<UAnimBlueprint> UDataTableManager::GetWeaponAnimInstance(EUnitBoneType bone, EWeaponAnimationType weapon)
{
	return unit_weapon_anim_asset_->GetUnitWeaponAnimInstance(bone, weapon);
}

TSubclassOf<AUnit> UDataTableManager::GetUnitType(ECharacterType type)
{
	return unit_type_asset_->GetUnitClass(type);
}

const TArray<FPerkNode>& UDataTableManager::GetTree() const
{
	return perk_tree_data_asset_->GetTree();
}

FHeroData UDataTableManager::GetHeroData(EHeroType type) const
{
	return hero_data_asset_->GetHeroData(type);
}
