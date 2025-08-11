/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.5.2025
Summary : Source file for Text Manager.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Managers/TextManager.h"

FText UTextManager::GetNameText(const FString& key) const
{
	return FText::FromStringTable(name_table_->GetStringTableId(), key);
}

FText UTextManager::GetDetailText(const FString& key) const
{
	return FText::FromStringTable(detail_table_->GetStringTableId(), key);
}

FText UTextManager::GetStatusText(ECharacterStatType stat_type) const
{
	FString key;
	switch (stat_type)
	{
	case ECharacterStatType::AttackPower:
		key = "ATK";
		break;
	case ECharacterStatType::AttackSpeed:
		key = "ATS";
		break;
	case ECharacterStatType::SkillPower:
		key = "SKP";
		break;
	case ECharacterStatType::SkillCoolDown:
		key = "SKCD";
		break;
	case ECharacterStatType::CriticalHitRate:
		key = "CRIT";
		break;
	case ECharacterStatType::EvasionRate:
		key = "DODGE";
		break;
	case ECharacterStatType::LifeSteal:
		key = "VAMP";
		break;
	case ECharacterStatType::MagazineBonus:
		key = "MAG_BONUS";
		break;
	case ECharacterStatType::ReloadSpeedBonus:
		key = "RELOAD_BONUS";
		break;
	}
	return FText::FromStringTable(status_table_->GetStringTableId(), key);
}

FText UTextManager::GetPopUpText(const FString& key) const
{
	return FText::FromStringTable(popup_table_->GetStringTableId(), key);
}

FText UTextManager::GetRuneNameText(ERuneSetType set_type) const
{
	return FText::FromStringTable(rune_name_table_->GetStringTableId(), RuneTypeToString(set_type));
}

FText UTextManager::GetRuneSetBonusText(ERuneSetType set_type, ERuneSetBonusType bonus_type) const
{
	switch (set_type)
	{
	case ERuneSetType::Chariot:
		return FText::FromStringTable(rune_chariot_set_bonus_table_->GetStringTableId(), RuneSetBonusTypeToString(bonus_type));
	case ERuneSetType::GreatBow:
		return FText::FromStringTable(rune_greatbow_set_bonus_table_->GetStringTableId(), RuneSetBonusTypeToString(bonus_type));
	case ERuneSetType::Dagger:
		return FText::FromStringTable(rune_dagger_set_bonus_table_->GetStringTableId(), RuneSetBonusTypeToString(bonus_type));
	case ERuneSetType::Quake:
		return FText::FromStringTable(rune_quake_set_bonus_table_->GetStringTableId(), RuneSetBonusTypeToString(bonus_type));
	case ERuneSetType::Tempest:
		return FText::FromStringTable(rune_tempest_bonus_table_->GetStringTableId(), RuneSetBonusTypeToString(bonus_type));
	case ERuneSetType::Viper:
		return FText::FromStringTable(rune_viper_bonus_table_->GetStringTableId(), RuneSetBonusTypeToString(bonus_type));
	case ERuneSetType::Poet:
		return FText::FromStringTable(rune_poet_set_bonus_table_->GetStringTableId(), RuneSetBonusTypeToString(bonus_type));
	default:
		return FText::FromName("INVALID");
	}
}
