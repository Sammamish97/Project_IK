/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 05.04.2025
Summary : Source file for data assets for character stats.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "DataAssets/CharacterStatDataAsset.h"

const FCharacterData& UCharacterStatDataAsset::GetCharacterData(EHeroType hero_type)
{
	checkf(character_data_map_.Find(hero_type), TEXT("Can't find stat type in the stat info data map!"));
	return character_data_map_[hero_type];
}

void UCharacterStatDataAsset::EnhanceCharacterData(EHeroType hero_type, ECharacterStatType stat_type, float increase_amount)
{
	checkf(character_data_map_.Find(hero_type), TEXT("Can't find stat type in the stat info data map!"));
	FCharacterData& data = character_data_map_[hero_type];
	switch (stat_type)
		{
		case ECharacterStatType::AttackPower:
			data.status_data_.attack_power_ += increase_amount;
			break;
		case ECharacterStatType::AttackSpeed:
			data.status_data_.attack_speed_ += increase_amount;
			break;
		case ECharacterStatType::CriticalHitRate:
			data.status_data_.critical_hit_rate_ += increase_amount;
			break;
		case ECharacterStatType::Accuracy:
			data.status_data_.accuracy_ += increase_amount;
			break;
		case ECharacterStatType::MagazineBonus:
			data.status_data_.magazine_bonus_ += increase_amount;
			break;
		case ECharacterStatType::LifeSteal:
			data.status_data_.life_steal_ += increase_amount;
			break;
		case ECharacterStatType::HitPoints:
			data.status_data_.hit_point_ += increase_amount;
			break;
		case ECharacterStatType::EvasionRate:
			data.status_data_.evasion_rate_ += increase_amount;
			break;
		case ECharacterStatType::Armor:
			data.status_data_.armor_ += increase_amount;
			break;
		case ECharacterStatType::Survivability:
			data.status_data_.survivability_ += increase_amount;
			break;
		case ECharacterStatType::SightRange:
			data.sight_range_ += increase_amount;
			break;
		case ECharacterStatType::MoveSpeed:
			data.move_speed_ += increase_amount;
			break;
		case ECharacterStatType::SkillPower:
			data.status_data_.skill_power_ += increase_amount;
			break;
		case ECharacterStatType::SkillCoolDown:
			data.status_data_.skill_cool_down_ += increase_amount;
			break;
		case ECharacterStatType::Shield:
		default:
			break;
		}
}

void UCharacterStatDataAsset::DiminishCharacterData(EHeroType hero_type, ECharacterStatType stat_type, float decrease_amount)
{
	checkf(character_data_map_.Find(hero_type), TEXT("Can't find stat type in the stat info data map!"));
	FCharacterData& data = character_data_map_[hero_type];
	switch (stat_type)
	{
	case ECharacterStatType::AttackPower:
		data.status_data_.attack_power_ -= decrease_amount;
		break;
	case ECharacterStatType::AttackSpeed:
		data.status_data_.attack_speed_ -= decrease_amount;
		break;
	case ECharacterStatType::CriticalHitRate:
		data.status_data_.critical_hit_rate_ -= decrease_amount;
		break;
	case ECharacterStatType::Accuracy:
		data.status_data_.accuracy_ -= decrease_amount;
		break;
	case ECharacterStatType::MagazineBonus:
		data.status_data_.magazine_bonus_ -= decrease_amount;
		break;
	case ECharacterStatType::LifeSteal:
		data.status_data_.life_steal_ -= decrease_amount;
		break;
	case ECharacterStatType::HitPoints:
		data.status_data_.hit_point_ -= decrease_amount;
		break;
	case ECharacterStatType::EvasionRate:
		data.status_data_.evasion_rate_ -= decrease_amount;
		break;
	case ECharacterStatType::Armor:
		data.status_data_.armor_ -= decrease_amount;
		break;
	case ECharacterStatType::Survivability:
		data.status_data_.survivability_ -= decrease_amount;
		break;
	case ECharacterStatType::SightRange:
		data.sight_range_ -= decrease_amount;
		break;
	case ECharacterStatType::MoveSpeed:
		data.move_speed_ -= decrease_amount;
		break;
	case ECharacterStatType::SkillPower:
		data.status_data_.skill_power_ -= decrease_amount;
		break;
	case ECharacterStatType::SkillCoolDown:
		data.status_data_.skill_cool_down_ -= decrease_amount;
		break;
	case ECharacterStatType::Shield:
	default:
		break;
	}
}
