/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.5.2025
Summary : Header file for the equip manager.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Managers/DataTableManager.h"
#include "Structs/RuneSetData.h"

#include "DataAssets/ActiveSkillDataAsset.h"
#include "DataAssets/RuneDataAsset.h"
#include "DataAssets/WeaponDataAsset.h"
#include "DataAssets/GlobalBuffDataAsset.h"
#include "DataAssets/PassiveSkillDataAsset.h"
#include "DataAssets/StatInfoDataAsset.h"
#include "DataAssets/CrowdControlInfoDataAsset.h"
#include "DataAssets/CharacterStatDataAsset.h"
#include "DataAssets/SupportSkillDataAsset.h"
#include "DataAssets/UnitTypeDataAsset.h"
#include "DataAssets/WeaponAnimDataAsset.h"
#include "DataAssets/PerkTreeDataAsset.h"
#include "Structs/SupportSkillData.h"
#include "Structs/WrapperEquipmentData.h"


FWeaponData UDataTableManager::GetWeaponStatusData(EWeaponType type) const
{
	return weapon_data_asset_->GetWeaponData(type);
}

FWeaponData UDataTableManager::GetWeaponDataRandomly(ERarity weight_rarity) const
{
	return weapon_data_asset_->GetWeaponDataRandomly(weight_rarity);
}

TArray<FWeaponData> UDataTableManager::GetUniqueWeaponDataRandomly(int32 n, ERarity weight_rarity) const
{
	return weapon_data_asset_->GetUniqueWeaponDataRandomly(n, weight_rarity);
}

FRuneSetData UDataTableManager::GetRuneSetData(ERuneSetType type) const
{
	return rune_data_asset_->GetRuneSetData(type);
}

FRuneSetData UDataTableManager::GetRuneSetDataRandomly(ERarity weight_rarity) const
{
	return rune_data_asset_->GetRuneSetDataRandomly(weight_rarity);
}

TArray<FRuneSetData> UDataTableManager::GetRuneSetDataRandomly(int32 n, ERarity weight_rarity) const
{
	return rune_data_asset_->GetRuneSetDataRandomly(n, weight_rarity);
}

TArray<FRuneSetData> UDataTableManager::GetUniqueRuneSetDataRandomly(int32 n, ERarity weight_rarity) const
{
	return rune_data_asset_->GetUniqueRuneSetDataRandomly(n, weight_rarity);
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
		return rune_data_asset_->GetRuneSetData(type).rune_set_data_[slot_num];
	}
	UE_LOG(LogTemp, Error, TEXT("rune_data_asset_ is invalid!"));
	return FRuneData();
}

FRuneData UDataTableManager::GetRuneDataRandomly(ERarity weight_rarity) const
{
	FRuneSetData randomly_chosen_set = rune_data_asset_->GetRuneSetDataRandomly(weight_rarity);
	return randomly_chosen_set.rune_set_data_[FMath::RandRange(0, 5)];
}

TArray<FRuneData> UDataTableManager::GetRuneDataRandomly(int32 n, ERarity weight_rarity) const
{
	TArray<FRuneSetData> set_array = rune_data_asset_->GetRuneSetDataRandomly(n, weight_rarity);

	TArray<FRuneData> result;
	for (const FRuneSetData& element : set_array)
	{
		result.Add(element.rune_set_data_[FMath::RandRange(0, 5)]);
	}
	return result;
}

TArray<FRuneData> UDataTableManager::GetUniqueRuneDataRandomly(int32 n, ERarity weight_rarity) const
{
	// @@ TODO: It will return less than N items if set_array has more than 6 same set types.
	TArray<FRuneSetData> set_array = rune_data_asset_->GetRuneSetDataRandomly(n, weight_rarity);

	TMap<ERuneSetType, TSet<int32>> unique_runes;
	TArray<FRuneData> result;

	for (const FRuneSetData& element : set_array)
	{
		// Shuffle indices 0-5 to ensure random selection without repeating from same set
		TArray<int32> indices = { 0, 1, 2, 3, 4, 5 };
		indices.Sort([](int32, int32) { return FMath::RandBool(); }); // Random shuffle

		for (int32 idx : indices)
		{
			const FRuneData& rune = element.rune_set_data_[idx];
			if (!unique_runes.Find(rune.set_type))
			{
				unique_runes.Add(rune.set_type);
			}
			if (!unique_runes[rune.set_type].Contains(rune.slot_number))
			{
				unique_runes[rune.set_type].Add(rune.slot_number);
				result.Add(rune);
				break; // Move to next FRuneSetData after adding one unique rune
			}
		}

		// Optional early exit if we already reached n unique entries
		if (result.Num() >= n)
		{
			break;
		}
	}

	return result;
}

UTexture2D* UDataTableManager::GetRuneSetThumbnail(ERuneSetType type) const
{
	return GetRuneSetData(type).item_data_.thumbnail;
}

FText UDataTableManager::GetRuneSetBonusDetail(ERuneSetType set_type, ERuneBonusType bonus_type) const
{
	return GetRuneSetData(set_type).bonus_details_[bonus_type];
}

FPassiveSkillData UDataTableManager::GetPassiveSkillData(EPassiveSkillType type) const
{
	return passive_skill_data_asset_->GetPassiveSkillData(type);
}

FPassiveSkillData UDataTableManager::GetPassiveSkillDataRandomly(ERarity weight_rarity) const
{
	return passive_skill_data_asset_->GetPassiveSkillDataRandomly(weight_rarity);
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

TArray<FActiveSkillData> UDataTableManager::GetUniqueActiveSkillDataRandomly(int32 n, ERarity weight_rarity) const
{
	return active_skill_data_asset_->GetUniqueActiveSkillDataRandomly(n, weight_rarity);
}

FSupportSkillData UDataTableManager::GetSupportSkillData(ESupportSkillType type) const
{
	return support_skill_data_asset_->GetSupportSkillData(type);
}

FString UDataTableManager::SupportSkillEnumToString(ESupportSkillType support_skill_type) const
{
	FString string;
	switch (support_skill_type)
	{
	case ESupportSkillType::Reposition:
		string = TEXT("Reposition");
		break;
	case ESupportSkillType::InstantRepair:
		string = TEXT("InstantRepair");
		break;
	case ESupportSkillType::SupportFire:
		string = TEXT("SupportFire");
		break;
	default:
		string = TEXT("Empty");
		break;
	}
	return string;
}

FSupportSkillData UDataTableManager::GetSupportSkillDataRandomly(ERarity weight_rarity) const
{
	return support_skill_data_asset_->GetSupportSkillDataRandomly(weight_rarity);
}

TArray<FSupportSkillData> UDataTableManager::GetUniqueSupportSkillDataRandomly(int32 n, ERarity weight_rarity) const
{
	return support_skill_data_asset_->GetUniqueSupportSkillDataRandomly(n, weight_rarity);
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

FSupportSkillData UDataTableManager::GetSupportSkillType(ESupportSkillType type)
{
	return support_skill_type_asset_->GetSupportSkillData(type);
}
const TArray<FPerkNode>& UDataTableManager::GetTree() const
{
	return perk_tree_data_asset_->GetTree();
}
