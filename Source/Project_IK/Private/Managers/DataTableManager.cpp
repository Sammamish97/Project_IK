/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.5.2025
Summary : Header file for the equip manager.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Managers/DataTableManager.h"

#include "DataAssets/WeaponDataAsset.h"
#include "DataAssets/GlobalBuffDataAsset.h"

FArmorData UDataTableManager::GetArmorData(EArmorType type)
{
	if (armor_table_)
	{
		return *armor_table_->FindRow<FArmorData>(*ArmorEnumToString(type), TEXT(""));
	}
	return *armor_table_->FindRow<FArmorData>(*ArmorEnumToString(EArmorType::Empty), TEXT(""));
}

FString UDataTableManager::ArmorEnumToString(EArmorType armor_type)
{
	FString string;
	switch (armor_type)
	{
	case EArmorType::TestArmor:
		string = TEXT("TestArmor");
		break;
	case EArmorType::TestHealth:
		string = TEXT("TestHealth");
		break;
	case EArmorType::TestDodge:
		string = TEXT("TestDodge");
		break;
	case EArmorType::TestSkillArmor:
		string = TEXT("TestSkillArmor");
		break;
	default:
		string = TEXT("Empty");
		break;
	}
	return string;
}

FTrinketData UDataTableManager::GetTrinketData(ETrinketType type)
{
	if (trinket_table_)
	{
		return *trinket_table_->FindRow<FTrinketData>(*TrinketEnumToString(type), TEXT(""));
	}
	return *trinket_table_->FindRow<FTrinketData>(*TrinketEnumToString(ETrinketType::Empty), TEXT(""));
}

FString UDataTableManager::TrinketEnumToString(ETrinketType trinket_type)
{
	FString string;
	switch (trinket_type)
	{
	case ETrinketType::TestAttack:
		string = TEXT("TestAttack");
		break;
	case ETrinketType::TestCrit:
		string = TEXT("TestCrit");
		break;
	case ETrinketType::TestAttackSpeed:
		string = TEXT("TestAttackSpeed");
		break;
	case ETrinketType::TestSkillTrinket:
		string = TEXT("TestSkillTrinket");
		break;
	default:
		string = TEXT("Empty");
		break;
	}
	return string;
}

FWeaponData UDataTableManager::GetWeaponData(EWeaponType type)
{
	if(weapon_data_asset_)
	{
		return weapon_data_asset_->weapon_data_map_[type];
	}
	//TODO: 적절한 예외처리가 필요함.
	return FWeaponData();
}

FString UDataTableManager::WeaponEnumToString(EWeaponType weapon_type)
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

FPassiveSkillData UDataTableManager::GetPassiveSkillData(EPassiveSkillType type)
{
	if (passive_skill_table_)
	{
		return *passive_skill_table_->FindRow<FPassiveSkillData>(*PassiveSkillEnumToString(type), TEXT(""));
	}
	return *passive_skill_table_->FindRow<FPassiveSkillData>(*PassiveSkillEnumToString(EPassiveSkillType::Empty), TEXT(""));
}

FString UDataTableManager::PassiveSkillEnumToString(EPassiveSkillType weapon_type)
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

FActiveSkillData UDataTableManager::GetActiveSkillData(EActiveSkillType type)
{
	if (active_skill_table_)
	{
		return *active_skill_table_->FindRow<FActiveSkillData>(*ActiveSkillEnumToString(type), TEXT(""));
	}
	return *active_skill_table_->FindRow<FActiveSkillData>(*ActiveSkillEnumToString(EActiveSkillType::Empty), TEXT(""));
}

FString UDataTableManager::ActiveSkillEnumToString(EActiveSkillType active_skill_type)
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

FOopartData UDataTableManager::GetOopartData(EOopartType type)
{
	if (oopart_table_)
	{
		return *oopart_table_->FindRow<FOopartData>(*OopartEnumToString(type), TEXT(""));
	}
	return *oopart_table_->FindRow<FOopartData>(*OopartEnumToString(EOopartType::Empty), TEXT(""));
}

FString UDataTableManager::OopartEnumToString(EOopartType oopart_type)
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

FGlobalBuffData UDataTableManager::GetGlobalBuffData(EGlobalBuffType buff_type)
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
