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

FRuneSetData UDataTableManager::GetRuneSetData(ERuneSetType type) const
{
	return rune_data_asset_->GetRuneSetData(type);
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
