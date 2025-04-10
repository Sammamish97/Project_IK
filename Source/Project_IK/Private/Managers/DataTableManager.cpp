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
#include "DataAssets/OopartDataAsset.h"
#include "DataAssets/PassiveSkillDataAsset.h"
#include "DataAssets/ItemDataAsset.h"
#include "Structs/CharacterData.h"

#include "Structs/WrapperEquipmentData.h"

#include "Managers/RandomDataAssetsManager.h"

FWeaponData UDataTableManager::GetWeaponData(EWeaponType type) const
{
	return weapon_data_asset_->GetWeaponData(type);
}

FString UDataTableManager::WeaponEnumToString(EWeaponType weapon_type) const
{
	FString string;
	switch (weapon_type)
	{
	case EWeaponType::Pistol:
		string = TEXT("Pistol");
		break;
	case EWeaponType::AssaultRifle:
		string = TEXT("AssaultRifle");
		break;
	case EWeaponType::ShotGun:
		string = TEXT("ShotGun");
		break;
	case EWeaponType::SniperRifle:
		string = TEXT("SniperRifle");
		break;
	default:
		string = TEXT("Empty");
		break;
	}
	return string;
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
	if(rune_data_asset_)
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
	return GetRuneSetData(type).thumbnail;
}

FPassiveSkillData UDataTableManager::GetPassiveSkillData(EPassiveSkillType type) const
{
	return passive_skill_data_asset_->GetPassiveSkillData(type);
}

FString UDataTableManager::PassiveSkillEnumToString(EPassiveSkillType weapon_type) const
{
	FString string;
	switch (weapon_type)
	{
	case EPassiveSkillType::FixedDmgReduce:
		string = TEXT("FixedDmgReduce");
		break;
	case EPassiveSkillType::RandDmgIncrease:
		string = TEXT("RandDmgIncrease");
		break;
	default:
		string = TEXT("Empty");
		break;
	}
	return string;
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

FString UDataTableManager::ActiveSkillEnumToString(EActiveSkillType active_skill_type) const
{
	FString string;
	switch (active_skill_type)
	{
	case EActiveSkillType::Thunder:
		string = TEXT("Thunder");
		break;
	case EActiveSkillType::RapidFire:
		string = TEXT("RapidFire");
		break;
	default:
		string = TEXT("Empty");
		break;
	}
	return string;
}

FActiveSkillData UDataTableManager::GetActiveSkillDataRandomly(ERarity weight_rarity) const
{
	return active_skill_data_asset_->GetActiveSkillDataRandomly(weight_rarity);
}

TArray<FActiveSkillData> UDataTableManager::GetUniqueActiveSkillDataRandomly(int32 n, ERarity weight_rarity) const
{
	return active_skill_data_asset_->GetUniqueActiveSkillDataRandomly(n, weight_rarity);
}

FOopartData UDataTableManager::GetOopartData(EOopartType type) const
{
	return oopart_data_asset_->GetOopartData(type);
}

FString UDataTableManager::OopartEnumToString(EOopartType oopart_type) const
{
	FString string;
	switch (oopart_type)
	{
	case EOopartType::HealingWaves:
		string = TEXT("HealingWaves");
		break;
	case EOopartType::AttackSpeedBoost:
		string = TEXT("AttackSpeedBoost");
		break;
	default:
		string = TEXT("Empty");
		break;
	}
	return string;
}

FOopartData UDataTableManager::GetOopartDataRandomly(ERarity weight_rarity) const
{
	return oopart_data_asset_->GetOopartDataRandomly(weight_rarity);
}

TArray<FOopartData> UDataTableManager::GetUniqueOopartDataRandomly(int32 n, ERarity weight_rarity) const
{
	return oopart_data_asset_->GetUniqueOopartDataRandomly(n, weight_rarity);
}

FItemData UDataTableManager::GetItemData(EItemType type) const
{
	return item_data_asset_->GetItemData(type);
}

FString UDataTableManager::ItemEnumToString(EItemType item_type) const
{
	FString string;
	switch (item_type)
	{
	case EItemType::HPPotion:
		string = TEXT("HPPotion");
		break;
	case EItemType::Missile:
		string = TEXT("Missile");
		break;
	case EItemType::Stimuli:
		string = TEXT("Stimuli");
		break;
	case EItemType::SmokeGrenade:
		string = TEXT("SmokeGrenade");
		break;
	case EItemType::Flashbang:
		string = TEXT("Flashbang");
		break;
	default:
		string = TEXT("Empty");
		break;
	}
	return string;
}

FItemData UDataTableManager::GetItemDataRandomly(ERarity weight_rarity) const
{
	return item_data_asset_->GetItemDataRandomly(weight_rarity);
}

TArray<FItemData> UDataTableManager::GetUniqueItemDataRandomly(int32 n, ERarity rarity) const
{
	return item_data_asset_->GetUniqueItemDataRandomly(n, rarity);
}

FCharacterData* UDataTableManager::GetCharacterData(EHeroType hero_type) const
{
	if (character_table_)
	{
		return character_table_->FindRow<FCharacterData>(*HeroEnumToString(hero_type), TEXT(""));
	}
	return nullptr;
}

FString UDataTableManager::HeroEnumToString(EHeroType char_type) const
{
	FString char_string;
	switch (char_type)
	{
	case EHeroType::Hero1:
		char_string = TEXT("1");
		break;
	case EHeroType::Hero2:
		char_string = TEXT("2");
		break;
	case EHeroType::Hero3:
		char_string = TEXT("3");
		break;
	case EHeroType::Hero4:
		char_string = TEXT("4");
		break;
	default:
		char_string = TEXT("1");
		break;
	}
	return char_string;
}

void UDataTableManager::EnhanceCharacterData(EHeroType hero_type, ECharacterStatType stat_type, float increase_amount)
{
	FCharacterData* data = GetCharacterData(hero_type);
	if (data)
	{
		switch (stat_type)
		{
		case ECharacterStatType::AttackPower:
			data->attack_power_ += increase_amount;
			break;
		case ECharacterStatType::AttackSpeed:
			data->attack_speed_ += increase_amount;
			break;
		case ECharacterStatType::CriticalHitRate:
			data->critical_hit_rate_ += increase_amount;
			break;
		case ECharacterStatType::Accuracy:
			data->accuracy_ += increase_amount;
			break;
		case ECharacterStatType::MagazineBonus:
			data->magazine_bonus_ += increase_amount;
			break;
		case ECharacterStatType::LifeSteal:
			data->life_steal_ += increase_amount;
			break;
		case ECharacterStatType::HitPoints:
			data->hit_point_ += increase_amount;
			break;
		case ECharacterStatType::EvasionRate:
			data->evasion_rate_ += increase_amount;
			break;
		case ECharacterStatType::Armor:
			data->armor_ += increase_amount;
			break;
		case ECharacterStatType::Survivability:
			data->survivability_ += increase_amount;
			break;
		case ECharacterStatType::SightRange:
			data->sight_range_ += increase_amount;
			break;
		case ECharacterStatType::MoveSpeed:
			data->move_speed_ += increase_amount;
			break;
		case ECharacterStatType::SkillPower:
			data->skill_power_ += increase_amount;
			break;
		case ECharacterStatType::SkillCoolDown:
			data->skill_cool_down_ += increase_amount;
			break;
		case ECharacterStatType::Shield:
		default:
			break;
		}
	}
}

void UDataTableManager::DiminishCharacterData(EHeroType hero_type, ECharacterStatType stat_type, float decrease_amount)
{
	FCharacterData* data = GetCharacterData(hero_type);
	if (data)
	{
		switch (stat_type)
		{
		case ECharacterStatType::AttackPower:
			data->attack_power_ -= decrease_amount;
			break;
		case ECharacterStatType::AttackSpeed:
			data->attack_speed_ -= decrease_amount;
			break;
		case ECharacterStatType::CriticalHitRate:
			data->critical_hit_rate_ -= decrease_amount;
			break;
		case ECharacterStatType::Accuracy:
			data->accuracy_ -= decrease_amount;
			break;
		case ECharacterStatType::MagazineBonus:
			data->magazine_bonus_ -= decrease_amount;
			break;
		case ECharacterStatType::LifeSteal:
			data->life_steal_ -= decrease_amount;
			break;
		case ECharacterStatType::HitPoints:
			data->hit_point_ -= decrease_amount;
			break;
		case ECharacterStatType::EvasionRate:
			data->evasion_rate_ -= decrease_amount;
			break;
		case ECharacterStatType::Armor:
			data->armor_ -= decrease_amount;
			break;
		case ECharacterStatType::Survivability:
			data->survivability_ -= decrease_amount;
			break;
		case ECharacterStatType::SightRange:
			data->sight_range_ -= decrease_amount;
			break;
		case ECharacterStatType::MoveSpeed:
			data->move_speed_ -= decrease_amount;
			break;
		case ECharacterStatType::SkillPower:
			data->skill_power_ -= decrease_amount;
			break;
		case ECharacterStatType::SkillCoolDown:
			data->skill_cool_down_ -= decrease_amount;
			break;
		case ECharacterStatType::Shield:
		default:
			break;
		}
	}
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
	int32 data_type = FMath::RandRange(0, 4);

	FWrapperEquipmentData result;
	switch (data_type)
	{
	case 0:
		result.active_skills_.Add(GetActiveSkillDataRandomly(weight_rarity));
		break;
	case 1:
		result.ooparts_.Add(GetOopartDataRandomly(weight_rarity));
		break;
	case 2:
		result.passive_skills_.Add(GetPassiveSkillDataRandomly(weight_rarity));
		break;
	case 3:
		result.runes_.Add(GetRuneDataRandomly(weight_rarity));
		break;
	case 4:
		result.weapons_.Add(GetWeaponDataRandomly(weight_rarity));
		break;
	default:
		break;
	}

	return result;
}

FWrapperEquipmentData UDataTableManager::GetUniqueEquipmentDataRandomly(int32 n, ERarity weight_rarity) const
{
	TArray<int32> data_counts({0, 0, 0, 0, 0});

	for (int32 i = 0; i < n; i++)
	{
		int32 index = FMath::RandRange(0, 4);

		// Increase count by randomly chosen data index
		data_counts[index] += 1;
	}

	FWrapperEquipmentData result;
	result.active_skills_ = GetUniqueActiveSkillDataRandomly(data_counts[0], weight_rarity);
	result.ooparts_ = GetUniqueOopartDataRandomly(data_counts[1], weight_rarity);
	result.passive_skills_ = GetUniquePassiveSkillDataRandomly(data_counts[2], weight_rarity);
	result.runes_ = GetUniqueRuneDataRandomly(data_counts[3], weight_rarity);
	result.weapons_ = GetUniqueWeaponDataRandomly(data_counts[4], weight_rarity);

	return result;
}
