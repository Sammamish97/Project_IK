/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.5.2025
Summary : Source file for Text Manager.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Managers/TextManager.h"

FText UTextManager::GetPerkNameText(EPerkNodeType key) const
{
	return FText::FromStringTable(perk_name_table_->GetStringTableId(), PerkEnumToKey(key));
}

FText UTextManager::GetPerkDetailText(EPerkNodeType key) const
{
	return FText::FromStringTable(perk_detail_table_->GetStringTableId(), PerkEnumToKey(key));
}

FText UTextManager::GetStatusText(ECharacterStatType stat_type) const
{
	return FText::FromStringTable(status_table_->GetStringTableId(), StatusEnumToKey(stat_type));
}

FText UTextManager::GetPopUpText(const FString& key) const
{
	return FText::FromStringTable(popup_table_->GetStringTableId(), key);
}

FText UTextManager::GetRuneNameText(ERuneSetType set_type) const
{
	return FText::FromStringTable(rune_name_table_->GetStringTableId(), RuneEnumToKey(set_type));
}

FText UTextManager::GetBuffNameText(EBuffType buff_type) const
{
	return FText::FromStringTable(buff_name_table_->GetStringTableId(), BuffEnumToKey(buff_type));
}

FText UTextManager::GetBuffDetailText(EBuffType buff_type) const
{
	return FText::FromStringTable(buff_detail_table_->GetStringTableId(), BuffEnumToKey(buff_type));
}

FText UTextManager::GetGlobalBuffNameText(EGlobalBuffType global_buff_type) const
{
	return FText::FromStringTable(buff_name_table_->GetStringTableId(), BuffEnumToKey(GlobalBuffEnumToBuffEnum(global_buff_type)));
}

FText UTextManager::GetGlobalBuffDetailText(EGlobalBuffType global_buff_type) const
{
	return FText::FromStringTable(buff_detail_table_->GetStringTableId(), BuffEnumToKey(GlobalBuffEnumToBuffEnum(global_buff_type)));
}

FText UTextManager::GetEventNameText(EEventType event_type) const
{
	return FText::FromStringTable(event_name_table_->GetStringTableId(), EventEnumToKey(event_type));
}

FText UTextManager::GetEventDetailText(EEventType event_type) const
{
	return FText::FromStringTable(event_detail_table_->GetStringTableId(), EventEnumToKey(event_type));
}

FText UTextManager::GetEventOptionText(EEventType event_type, int32 option_idx) const
{
	switch (option_idx)
	{
		case 0:
			return FText::FromStringTable(event_option_1_table_->GetStringTableId(), EventEnumToKey(event_type));
		case 1:
			return FText::FromStringTable(event_option_2_table_->GetStringTableId(), EventEnumToKey(event_type));
		case 2:
			return FText::FromStringTable(event_option_3_table_->GetStringTableId(), EventEnumToKey(event_type));
		case 3:
			return FText::FromStringTable(event_option_4_table_->GetStringTableId(), EventEnumToKey(event_type));
	default:
		return FText::FromName("INVALID");
	}
	
}

FText UTextManager::GetRuneSetBonusText(ERuneSetType set_type, ERuneSetBonusType bonus_type) const
{
	switch (bonus_type)
	{
	case ERuneSetBonusType::Edge:
		return FText::FromStringTable(rune_edge_bonus_table_->GetStringTableId(), RuneEnumToKey(set_type));
	case ERuneSetBonusType::Triangle:
		return FText::FromStringTable(rune_triangle_bonus_table_->GetStringTableId(), RuneEnumToKey(set_type));
	case ERuneSetBonusType::Hexagon:
		return FText::FromStringTable(rune_hexagon_bonus_table_->GetStringTableId(), RuneEnumToKey(set_type));
	default:
		return FText::FromName("INVALID");
	}
}

FText UTextManager::GetWeaponNameText(EWeaponType type) const
{
	return FText::FromStringTable(weapon_name_table_->GetStringTableId(), WeaponEnumToKey(type));
}

FText UTextManager::GetWeaponDetailText(EWeaponType type) const
{
	return FText::FromStringTable(weapon_detail_table_->GetStringTableId(), WeaponEnumToKey(type));
}

FText UTextManager::GetActiveSkillNameText(EActiveSkillType type) const
{
	return FText::FromStringTable(active_skill_name_table_->GetStringTableId(), ActiveSkillEnumToKey(type));
}

FText UTextManager::GetActiveSkillDetailText(EActiveSkillType type) const
{
	return FText::FromStringTable(active_skill_detail_table_->GetStringTableId(), ActiveSkillEnumToKey(type));
}

FText UTextManager::GetPassiveSkillNameText(EPassiveSkillType type) const
{
	return FText::FromStringTable(passive_skill_name_table_->GetStringTableId(), PassiveSkillEnumToKey(type));
}

FText UTextManager::GetPassiveSkillDetailText(EPassiveSkillType type) const
{
	return FText::FromStringTable(passive_skill_detail_table_->GetStringTableId(), PassiveSkillEnumToKey(type));
}

FText UTextManager::GetSupportSkillNameText(ESupportSkillType type) const
{
	return FText::FromStringTable(support_skill_name_table_->GetStringTableId(), SupportSkillEnumToKey(type));
}

FText UTextManager::GetSupportSkillDetailText(ESupportSkillType type) const
{
	return FText::FromStringTable(support_skill_detail_table_->GetStringTableId(), SupportSkillEnumToKey(type));
}

FString UTextManager::RuneEnumToKey(ERuneSetType type) const
{
	switch (type)
	{
	case ERuneSetType::Chariot:
		return FString("CHARIOT");
	case ERuneSetType::GreatBow:
		return FString("GREATBOW");
	case ERuneSetType::Dagger:
		return FString("DAGGER");
	case ERuneSetType::Quake:
		return FString("QUAKE");
	case ERuneSetType::Tempest:
		return FString("TEMPEST");
	case ERuneSetType::Viper:
		return FString("VIPER");
	default:
		return FString("INVALID");
	}
}


FString UTextManager::RuneSetBonusEnumToKey(ERuneSetBonusType type) const
{
	switch (type)
	{
	case ERuneSetBonusType::Edge:
		return FString("EDGE");
	case ERuneSetBonusType::Triangle:
		return FString("TRIANGLE");
	case ERuneSetBonusType::Hexagon:
		return FString("HEXAGON");
	default:
		return FString("INVALID");
	}
}

FString UTextManager::WeaponEnumToKey(EWeaponType weapon_type) const
{
	FString key;
	switch (weapon_type)
	{
	case EWeaponType::DefaultPistol:
		key = "DP";
		break;
	case EWeaponType::Pistol_B:
		key = "PT_B";
		break;
	case EWeaponType::AssaultRifle_B:
		key = "AR_B";
		break;
	case EWeaponType::ShotGun_B:
		key = "SG_B";
		break;
	case EWeaponType::SniperRifle_B:
		key = "SNR_B";
		break;
	case EWeaponType::Pistol_A:
		key = "PT_A";
		break;
	case EWeaponType::AssaultRifle_A:
		key = "AR_A";
		break;
	case EWeaponType::ShotGun_A:
		key = "SG_A";
		break;
	case EWeaponType::SniperRifle_A:
		key = "SNR_A";
		break;
	case EWeaponType::HeavyGunnerWeapon:
		key = "HGW";
		break;
	case EWeaponType::OfficerWeapon:
		key = "OFW";
		break;
	case EWeaponType::AssassinWeapon:
		key = "ASW";
		break;
	}
	return key;
}

FString UTextManager::ActiveSkillEnumToKey(EActiveSkillType active_skill_type) const
{
	FString key;
	switch (active_skill_type)
	{
	case EActiveSkillType::Thunder_B:
		key = "TD_B";
		break;
	case EActiveSkillType::Thunder_A:
		key = "TD_A";
		break;
	case EActiveSkillType::ThunderStorm_B:
		key = "TDS_B";
		break;
	case EActiveSkillType::ThunderStorm_A:
		key = "TDS_A";
		break;
	case EActiveSkillType::FateSpiral_B:
		key = "FS_B";
		break;
	case EActiveSkillType::FateSpiral_A:
		key = "FS_A";
		break;
	case EActiveSkillType::Encourage_B:
		key = "EC_B";
		break;
	case EActiveSkillType::Encourage_A:
		key = "EC_A";
		break;
	case EActiveSkillType::DeploySentryGun_B:
		key = "DS_B";
		break;
	case EActiveSkillType::DeploySentryGun_A:
		key = "DS_A";
		break;
	case EActiveSkillType::TripleFire_B:
		key = "TF_B";
		break;
	case EActiveSkillType::TripleFire_A:
		key = "TF_A";
		break;
	case EActiveSkillType::ChargeShot_B:
		key = "CS_B";
		break;
	case EActiveSkillType::ChargeShot_A:
		key = "CS_A";
		break;
	case EActiveSkillType::MagnetizedBullet_B:
		key = "MTB_B";
		break;
	case EActiveSkillType::MagnetizedBullet_A:
		key = "MTB_A";
		break;
	case EActiveSkillType::Ricochet_B:
		key = "RC_B";
		break;
	case EActiveSkillType::Ricochet_A:
		key = "RC_A";
		break;
	}
	return key;
}

FString UTextManager::PassiveSkillEnumToKey(EPassiveSkillType passive_skill_type) const
{
	FString key;
	switch (passive_skill_type)
	{
	case EPassiveSkillType::Agility:
		key = "AG";
		break;
	case EPassiveSkillType::CloseQuartersMastery:
		key = "CQM";
		break;
	case EPassiveSkillType::Executioner:
		key = "EC";
		break;
	case EPassiveSkillType::Berserker:
		key = "BSK";
		break;
	case EPassiveSkillType::StableFirstRound:
		key = "SFR";
		break;
	case EPassiveSkillType::RunAndGun:
		key = "RAG";
		break;
	case EPassiveSkillType::QuickHands:
		key = "QH";
		break;
	case EPassiveSkillType::Composed:
		key = "CS";
		break;
	case EPassiveSkillType::OptimizedCore:
		key = "OC";
		break;
	case EPassiveSkillType::ReinforcedCore:
		key = "RIC";
		break;
	case EPassiveSkillType::SlopedArmor:
		key = "SA";
		break;
	case EPassiveSkillType::ExtraPadding:
		key = "EPD";
		break;
	case EPassiveSkillType::AcceleratedBarrel:
		key = "AB";
		break;
	case EPassiveSkillType::EnhancedPistons:
		key = "EPT";
		break;
	case EPassiveSkillType::ReinforcedCamera:
		key = "RC";
		break;
	case EPassiveSkillType::Conductor:
		key = "CDT";
		break;
	}
	return key;
}

FString UTextManager::SupportSkillEnumToKey(ESupportSkillType support_skill_type) const
{
	FString key;
	switch (support_skill_type)
	{
	case ESupportSkillType::Reposition:
		key = "RP";
		break;
	case ESupportSkillType::SetAttackTarget:
		key = "SAT";
		break;
	case ESupportSkillType::Maintain:
		key = "MT";
		break;
	}
	return key;
}

FString UTextManager::StatusEnumToKey(ECharacterStatType stat_type) const
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
	case ECharacterStatType::HitPoints:
		key = "HP";
		break;
	case ECharacterStatType::Armor:
		key = "ARMOR";
		break;
	case ECharacterStatType::Survivability:
		key = "SURV";
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
	return key;
}

FString UTextManager::BuffEnumToKey(EBuffType buff_type) const
{
	FString key;
	switch (buff_type)
	{
	case EBuffType::MagnetizedBullet_A:
		key = "MTB";
		break;
	case EBuffType::Ricochet:
		key = "RC";
		break;
	case EBuffType::TripleFire:
		key = "TPF";
		break;
	case EBuffType::Encourage:
		key = "EC";
		break;
	case EBuffType::Agility:
		key = "AG";
		break;
	case EBuffType::CloseQuartersMastery:
		key = "CQM";
		break;
	case EBuffType::Executioner:
		key = "EXC";
		break;
	case EBuffType::Berserker:
		key = "BSK";
		break;
	case EBuffType::StableFirstRound:
		key = "SFR";
		break;
	case EBuffType::RunAndGun:
		key = "RNG";
		break;
	case EBuffType::QuickHands:
		key = "QH";
		break;
	case EBuffType::Composure:
		key = "CPS";
		break;
	case EBuffType::OptimizedCore:
		key = "OTC";
		break;
	case EBuffType::ReinforcedCore:
		key = "RICORE";
		break;
	case EBuffType::SlopedArmor:
		key = "SPR";
		break;
	case EBuffType::ExtraPadding:
		key = "ETP";
		break;
	case EBuffType::AcceleratedBarrel:
		key = "ACB";
		break;
	case EBuffType::EnhancedPiston:
		key = "EP";
		break;
	case EBuffType::ReinforcedCamera:
		key = "RICAMERA";
		break;
	case EBuffType::Conductor:
		key = "CDT";
		break;
	case EBuffType::Maintain:
		key = "MT";
		break;
	case EBuffType::Chariot_Edge:
		key = "CHA_E";
		break;
	case EBuffType::Chariot_Triangle:
		key = "CHA_T";
		break;
	case EBuffType::Chariot_Hexagon:
		key = "CHA_H";
		break;
	case EBuffType::Dagger_Edge:
		key = "DAG_E";
		break;
	case EBuffType::Dagger_Triangle:
		key = "DAG_T";
		break;
	case EBuffType::Dagger_Hexagon:
		key = "DAG_H";
		break;
	case EBuffType::Quake_Edge:
		key = "QAK_E";
		break;
	case EBuffType::Quake_Triangle:
		key = "QAK_T";
		break;
	case EBuffType::Quake_Hexagon:
		key = "QAK_H";
		break;
	case EBuffType::Viper_Edge:
		key = "VIP_E";
		break;
	case EBuffType::Viper_Triangle:
		key = "VIP_T";
		break;
	case EBuffType::Viper_Hexagon:
		key = "VIP_H";
		break;
	case EBuffType::Soldier_A:
		key = "SD_A";
		break;
	case EBuffType::Knight_A:
		key = "KN_A";
		break;
	case EBuffType::Officer_Focusing:
		key = "OF_FOCUS";
		break;
	case EBuffType::Officer_Marked:
		key = "OF_MARKED";
		break;
	case EBuffType::Officer_A_ForceShield:
		key = "OF_SHIELD";
		break;
	case EBuffType::OnAllyDead:
		key = "ON_ALLY_DEAD";
		break;
	case EBuffType::Deathbound:
		key = "DB";
		break;
	case EBuffType::Upgrade_Alpha:
		key = "UPA";
		break;
	case EBuffType::Upgrade_Beta:
		key = "UPB";
		break;
	case EBuffType::Upgrade_Gamma:
		key = "UPG";
		break;
	case EBuffType::Upgrade_Omega:
		key = "UPO";
		break;
	case EBuffType::AirStrikeArmorDebuff:
		key = "ASK_ARM";
		break;
	case EBuffType::AirStrikeHPDebuff:
		key = "ASK_HP";
		break;
	case EBuffType::AmbushAttackSpeedDebuff:
		key = "AB_AS";
		break;
	case EBuffType::AmbushAttackPowerDebuff:
		key = "AB_AP";
		break;
	case EBuffType::EMPCritBuff:
		key = "EMP_CR";
		break;
	case EBuffType::EMPAttackSpeedBuff:
		key = "EMP_AS";
		break;
	case EBuffType::EMPHPDebuff:
		key = "EMP_HP";
		break;
	case EBuffType::ProtocolSurvive_Shield:
		key = "PRS_SHD";
		break;
	case EBuffType::ProtocolSurvive_LifeSteal:
		key = "PRS_VAMP";
		break;
	case EBuffType::ProtocolAssault_AttackPowerBuff:
		key = "PRA_ATP";
		break;
	case EBuffType::ProtocolAssault_SkillPowerBuff:
		key = "PRA_SP";
		break;
	case EBuffType::ProtocolAssault_AttackSpeedBuff:
		key = "PRA_AS";
		break;
	case EBuffType::ProtocolEfficiency_CritBuff:
		key = "PRE_CRIT";
		break;
	case EBuffType::ProtocolEfficiency_EvadeBuff:
		key = "PRE_DODGE";
		break;
	case EBuffType::ProtocolEfficiency_CooldownBuff:
		key = "PRE_CD";
		break;
	case EBuffType::Recon_RemoveNegativeEvents:
		key = "RC_RNE";
		break;
	case EBuffType::Recon_RewardChoiceBuff:
		key = "RC_RCH";
		break;
	case EBuffType::Recon_CreditBonusBuff:
		key = "RC_CR";
		break;
	case EBuffType::SetTrap_HPDebuff:
		key = "ST_HP";
		break;
	case EBuffType::Core_AttackBuff:
		key = "C_ATP_B";
		break;
	case EBuffType::Core_AttackDebuff:
		key = "C_ATP_DB";
		break;
	case EBuffType::Patrol_RandomBuff1:
		key = "PAT_RB1";
		break;
	case EBuffType::Patrol_RandomDebuff1:
		key = "PAT_RDB1";
		break;
	case EBuffType::Patrol_RandomBuff2:
		key = "PAT_RB2";
		break;
	case EBuffType::Patrol_RandomDebuff2:
		key = "PAT_RDB2";
		break;
	case EBuffType::Patrol_RandomBuff3:
		key = "PAT_RB3";
		break;
	case EBuffType::Patrol_RandomDebuff3:
		key = "PAT_RDB3";
		break;
	case EBuffType::Patrol_RandomBuff4:
		key = "PAT_RB4";
		break;
	case EBuffType::Patrol_RandomDebuff4:
		key = "PAT_RDB4";
		break;

	case EBuffType::Acquire_Shield:
		key = "ACS";
		break;

	case EBuffType::WoundingBullets:
		key = "WB";
		break;

	case EBuffType::Trap_RewardCandidateDebuff:
		key = "TR_RCAD";
		break;

	case EBuffType::Trap_RewardChoiceDebuff:
		key = "TR_RCOD";
		break;
	}
	return key;
}

FString UTextManager::GlobalBuffEnumToKey(EGlobalBuffType global_buff_type) const
{
	FString key;
	switch (global_buff_type)
	{
	case EGlobalBuffType::WoundingBullets:
		key = "WB";
		break;
	case EGlobalBuffType::Deathbound_Hero1:
		key = "DB1";
		break;
	case EGlobalBuffType::Deathbound_Hero2:
		key = "DB2";
		break;
	case EGlobalBuffType::Deathbound_Hero3:
		key = "DB3";
		break;
	case EGlobalBuffType::Deathbound_Hero4:
		key = "DB4";
		break;
	case EGlobalBuffType::Upgrade_Alpha:
		key = "UPA";
		break;
	case EGlobalBuffType::Upgrade_Beta:
		key = "UPB";
		break;
	case EGlobalBuffType::Upgrade_Gamma:
		key = "UPG";
		break;
	case EGlobalBuffType::Upgrade_Omega:
		key = "UPO";
		break;
	case EGlobalBuffType::Acquire_Shield:
		key = "ACS";
		break;
	case EGlobalBuffType::AirStrike_ArmorDebuff:
		key = "ASK_ARM";
		break;
	case EGlobalBuffType::AirStrike_HPDebuff:
		key = "ASK_HP";
		break;
	case EGlobalBuffType::Ambush_AttackSpeedDebuff:
		key = "AB_AS";
		break;
	case EGlobalBuffType::Ambush_AttackPowerDebuff:
		key = "AB_AP";
		break;
	case EGlobalBuffType::Trap_RewardCandidateDebuff:
		key = "T_RCD";
		break;
	case EGlobalBuffType::Trap_RewardChoiceDebuff:
		key = "TR_RCH";
		break;
	case EGlobalBuffType::EMP_CritBuff:
		key = "EMP_CR";
		break;
	case EGlobalBuffType::EMP_AttackSpeedBuff:
		key = "EMP_AS";
		break;
	case EGlobalBuffType::EMP_HPDebuff:
		key = "EMP_HP";
		break;
	case EGlobalBuffType::ProtocolSurvive_Shield:
		key = "PRS_SHD";
		break;
	case EGlobalBuffType::ProtocolSurvive_LifeSteal:
		key = "PRS_VAMP";
		break;
	case EGlobalBuffType::ProtocolAssault_AttackPowerBuff:
		key = "PRA_ATP";
		break;
	case EGlobalBuffType::ProtocolAssault_SkillPowerBuff:
		key = "PRA_SP";
		break;
	case EGlobalBuffType::ProtocolAssault_AttackSpeedBuff:
		key = "PRA_AS";
		break;
	case EGlobalBuffType::ProtocolEfficiency_CritBuff:
		key = "PRE_CRIT";
		break;
	case EGlobalBuffType::ProtocolEfficiency_EvadeBuff:
		key = "PRE_DODGE";
		break;
	case EGlobalBuffType::ProtocolEfficiency_CooldownBuff:
		key = "PRE_CD";
		break;
	case EGlobalBuffType::Recon_RemoveNegativeEvents:
		key = "RC_RNE";
		break;
	case EGlobalBuffType::Recon_RewardChoiceBuff:
		key = "RC_RCH";
		break;
	case EGlobalBuffType::Recon_CreditBonusBuff:
		key = "RC_CR";
		break;
	case EGlobalBuffType::SetTrap_HPDebuff:
		key = "ST_HP";
		break;
	case EGlobalBuffType::Core_AttackBuff:
		key = "C_ATP_B";
		break;
	case EGlobalBuffType::Core_AttackDebuff:
		key = "C_ATP_DB";
		break;
	case EGlobalBuffType::Patrol_RandomBuff1:
		key = "PAT_RB1";
		break;
	case EGlobalBuffType::Patrol_RandomDebuff1:
		key = "PAT_RDB1";
		break;
	case EGlobalBuffType::Patrol_RandomBuff2:
		key = "PAT_RB2";
		break;
	case EGlobalBuffType::Patrol_RandomDebuff2:
		key = "PAT_RDB2";
		break;
	case EGlobalBuffType::Patrol_RandomBuff3:
		key = "PAT_RB3";
		break;
	case EGlobalBuffType::Patrol_RandomDebuff3:
		key = "PAT_RDB3";
		break;
	case EGlobalBuffType::Patrol_RandomBuff4:
		key = "PAT_RB4";
		break;
	case EGlobalBuffType::Patrol_RandomDebuff4:
		key = "PAT_RDB4";
		break;
	}
	return key;
}

//Global Buff와 Buff는 Text를 공유한다. 그러므로 타입을 변환하는 함수를 추가한다.
EBuffType UTextManager::GlobalBuffEnumToBuffEnum(EGlobalBuffType global_buff_type) const
{
	switch (global_buff_type)
	{
	case EGlobalBuffType::WoundingBullets:
		return EBuffType::WoundingBullets;

	case EGlobalBuffType::Acquire_Shield:
		return EBuffType::Acquire_Shield;
		
	case EGlobalBuffType::Trap_RewardCandidateDebuff:
		return EBuffType::Trap_RewardCandidateDebuff;
		
	case EGlobalBuffType::Trap_RewardChoiceDebuff:
		return EBuffType::Trap_RewardChoiceDebuff;
		
	case EGlobalBuffType::Deathbound_Hero1:
	case EGlobalBuffType::Deathbound_Hero2:
	case EGlobalBuffType::Deathbound_Hero3:
	case EGlobalBuffType::Deathbound_Hero4:
		return EBuffType::Deathbound;
		
	case EGlobalBuffType::Upgrade_Alpha:
		return EBuffType::Upgrade_Alpha;
		
	case EGlobalBuffType::Upgrade_Beta:
		return EBuffType::Upgrade_Beta;

	case EGlobalBuffType::Upgrade_Gamma:
		return EBuffType::Upgrade_Gamma;
		
	case EGlobalBuffType::Upgrade_Omega:
		return EBuffType::Upgrade_Omega;

	
	case EGlobalBuffType::AirStrike_ArmorDebuff:
		return EBuffType::AirStrikeArmorDebuff;
		
	case EGlobalBuffType::AirStrike_HPDebuff:
		return EBuffType::AirStrikeHPDebuff;
		
	case EGlobalBuffType::Ambush_AttackSpeedDebuff:
		return EBuffType::AmbushAttackSpeedDebuff;
		
	case EGlobalBuffType::Ambush_AttackPowerDebuff:
		return EBuffType::AmbushAttackPowerDebuff;
	
	case EGlobalBuffType::EMP_CritBuff:
		return EBuffType::EMPCritBuff;
		
	case EGlobalBuffType::EMP_AttackSpeedBuff:
		return EBuffType::EMPAttackSpeedBuff;
		
	case EGlobalBuffType::EMP_HPDebuff:
		return EBuffType::EMPHPDebuff;
		
	case EGlobalBuffType::ProtocolSurvive_Shield:
		return EBuffType::ProtocolSurvive_Shield;
		
	case EGlobalBuffType::ProtocolSurvive_LifeSteal:
		return EBuffType::ProtocolSurvive_LifeSteal;
		
	case EGlobalBuffType::ProtocolAssault_AttackPowerBuff:
		return EBuffType::ProtocolAssault_AttackPowerBuff;

	case EGlobalBuffType::ProtocolAssault_SkillPowerBuff:
		return EBuffType::ProtocolAssault_SkillPowerBuff;

	case EGlobalBuffType::ProtocolAssault_AttackSpeedBuff:
		return EBuffType::ProtocolAssault_AttackSpeedBuff;

	case EGlobalBuffType::ProtocolEfficiency_CritBuff:
		return EBuffType::ProtocolEfficiency_CritBuff;

	case EGlobalBuffType::ProtocolEfficiency_EvadeBuff:
		return EBuffType::ProtocolEfficiency_EvadeBuff;

	case EGlobalBuffType::ProtocolEfficiency_CooldownBuff:
		return EBuffType::ProtocolEfficiency_CooldownBuff;

	case EGlobalBuffType::Recon_RemoveNegativeEvents:
		return EBuffType::Recon_RemoveNegativeEvents;

	case EGlobalBuffType::Recon_RewardChoiceBuff:
		return EBuffType::Recon_RewardChoiceBuff;

	case EGlobalBuffType::Recon_CreditBonusBuff:
		return EBuffType::Recon_CreditBonusBuff;

	case EGlobalBuffType::SetTrap_HPDebuff:
		return EBuffType::SetTrap_HPDebuff;
		
	case EGlobalBuffType::Core_AttackBuff:
		return EBuffType::Core_AttackBuff;
		
	case EGlobalBuffType::Core_AttackDebuff:
		return EBuffType::Core_AttackDebuff;
		
	case EGlobalBuffType::Patrol_RandomBuff1:
		return EBuffType::Patrol_RandomBuff1;
		
	case EGlobalBuffType::Patrol_RandomDebuff1:
		return EBuffType::Patrol_RandomDebuff1;
		
	case EGlobalBuffType::Patrol_RandomBuff2:
		return EBuffType::Patrol_RandomBuff2;
		
	case EGlobalBuffType::Patrol_RandomDebuff2:
		return EBuffType::Patrol_RandomDebuff2;
		
	case EGlobalBuffType::Patrol_RandomBuff3:
		return EBuffType::Patrol_RandomBuff3;
		
	case EGlobalBuffType::Patrol_RandomDebuff3:
		return EBuffType::Patrol_RandomDebuff3;
		
	case EGlobalBuffType::Patrol_RandomBuff4:
		return EBuffType::Patrol_RandomBuff4;
		
	case EGlobalBuffType::Patrol_RandomDebuff4:
		return EBuffType::Patrol_RandomDebuff4;

	default:
		return EBuffType::INVALID;
	}
}


FString UTextManager::EventEnumToKey(EEventType event_type) const
{
	FString key;
	switch (event_type)
	{
	case EEventType::Ambush:
		key = "AMBUSH";
		break;
	case EEventType::Core:
		key = "CORE";
		break;
	case EEventType::Patrol:
		key = "PATROL";
		break;
	case EEventType::Trap:
		key = "TRAP";
		break;
	case EEventType::Recon:
		key = "RECON";
		break;
	case EEventType::AbandonedSupply:
		key = "SUPPLY";
		break;
	case EEventType::AirStrike:
		key = "AIRSTRIKE";
		break;
	case EEventType::ProtocolAssault:
		key = "PRO_ASSAULT";
		break;
	case EEventType::ProtocolSurvive:
		key = "PRO_SURVIVE";
		break;
	case EEventType::ProtocolEfficiency:
		key = "PRO_EFFICIENCY";
		break;
	case EEventType::SetTrap:
		key = "SETTRAP";
		break;
	case EEventType::EMP:
		key = "EMP";
		break;
	}
	return key;
}

FString UTextManager::PerkEnumToKey(EPerkNodeType type) const
{
	FString key;
	switch (type)
	{
	case EPerkNodeType::EXALPHA:
		key = "EXALPHA";
		break;
	case EPerkNodeType::EXBETA:
		key = "EXBETA";
		break;
	case EPerkNodeType::EXGAMMA:
		key = "EXGAMMA";
		break;
	case EPerkNodeType::EXOMEGA:
		key = "EXOMEGA";
		break;
	case EPerkNodeType::EXARM_1:
		key = "EXARM_1";
		break;
	case EPerkNodeType::EXARM_2:
		key = "EXARM_2";
		break;
	case EPerkNodeType::EXATK_1:
		key = "EXATK_1";
		break;
	case EPerkNodeType::EXATK_2:
		key = "EXATK_2";
		break;
	case EPerkNodeType::EXATS_1:
		key = "EXATS_1";
		break;
	case EPerkNodeType::EXATS_2:
		key = "EXATS_2";
		break;
	case EPerkNodeType::EXCREDIT_1:
		key = "EXCREDIT_1";
		break;
	case EPerkNodeType::EXCREDIT_2:
		key = "EXCREDIT_2";
		break;
	case EPerkNodeType::EXCRIT:
		key = "EXCRIT";
		break;
	case EPerkNodeType::EXDODGE:
		key = "EXDODGE";
		break;
	case EPerkNodeType::EXGOTCHA_1:
		key = "EXGOTCHA_1";
		break;
	case EPerkNodeType::EXGOTCHA_2:
		key = "EXGOTCHA_2";
		break;
	case EPerkNodeType::EXGOTCHA_3:
		key = "EXGOTCHA_3";
		break;
	case EPerkNodeType::EXHEAL_1:
		key = "EXHEAL_1";
		break;
	case EPerkNodeType::EXHEAL_2:
		key = "EXHEAL_2";
		break;
	case EPerkNodeType::EXHEAL_3:
		key = "EXHEAL_3";
		break;
	case EPerkNodeType::EXHP_1:
		key = "EXHP_1";
		break;
	case EPerkNodeType::EXHP_2:
		key = "EXHP_2";
		break;
	case EPerkNodeType::EXINITSHIELD:
		key = "EXINITSHIELD";
		break;
	case EPerkNodeType::EXPASSIVE_1:
		key = "EXPASSIVE_1";
		break;
	case EPerkNodeType::EXPASSIVE_2:
		key = "EXPASSIVE_2";
		break;
	case EPerkNodeType::EXREWARDCHOOSE_1:
		key = "EXREWARDCHOOSE_1";
		break;
	case EPerkNodeType::EXREWARDCHOOSE_2:
		key = "EXREWARDCHOOSE_2";
		break;
	case EPerkNodeType::EXREWARDCOUNT_1:
		key = "EXREWARDCOUNT_1";
		break;
	case EPerkNodeType::EXREWARDCOUNT_2:
		key = "EXREWARDCOUNT_2";
		break;
	case EPerkNodeType::EXSKP:
		key = "EXSKP";
		break;
	case EPerkNodeType::EXSURV:
		key = "EXSURV";
		break;
	}
	return key;
}
