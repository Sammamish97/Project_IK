/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.5.2025
Summary : Source file for the equip manager.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Managers/EquipManager.h"

#include "Structs/PassiveSkillData.h"

UEquipManager::UEquipManager()
{
	FString armor_data_path = TEXT("/Script/Engine.DataTable'/Game/Resources/IK_Armor_Data.IK_Armor_Data'");
	static ConstructorHelpers::FObjectFinder<UDataTable> dt_armor_data(*armor_data_path);
	if (dt_armor_data.Succeeded() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance has failed to load a armor file data (IK_Armor_Data)"));
	}
	armor_table_= dt_armor_data.Object;

	FString trinket_data_path = TEXT("/Script/Engine.DataTable'/Game/Resources/IK_Trinket_Data.IK_Trinket_Data'");
	static ConstructorHelpers::FObjectFinder<UDataTable> dt_trinket_data(*trinket_data_path);
	if (dt_trinket_data.Succeeded() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance has failed to load a Trinket file data (IK_Trinket_Data)"));
	}
	trinket_table_= dt_trinket_data.Object;

	FString weapon_data_path = TEXT("/Script/Engine.DataTable'/Game/Resources/IK_Weapon_Data.IK_Weapon_Data'");
	static ConstructorHelpers::FObjectFinder<UDataTable> dt_weapon_data(*weapon_data_path);
	if (dt_weapon_data.Succeeded() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance has failed to load a Weapon file data (IK_Weapon_Data)"));
	}
	weapon_table_= dt_weapon_data.Object;

	FString passive_data_path = TEXT("/Script/Engine.DataTable'/Game/Resources/IK_Passive_Skill_Data.IK_Passive_Skill_Data'");
	static ConstructorHelpers::FObjectFinder<UDataTable> dt_passive_skill_data(*passive_data_path);
	if (dt_passive_skill_data.Succeeded() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance has failed to load a passive skill file data (IK_Passive_Skill_Data)"));
	}
	passive_skill_table_= dt_passive_skill_data.Object;
}

FArmorData UEquipManager::GetArmorData(EArmorType type)
{
	if (armor_table_)
	{
		return *armor_table_->FindRow<FArmorData>(*ArmorEnumToString(type), TEXT(""));
	}
	return *armor_table_->FindRow<FArmorData>(*ArmorEnumToString(EArmorType::Empty), TEXT(""));
}

FString UEquipManager::ArmorEnumToString(EArmorType armor_type)
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

FTrinketData UEquipManager::GetTrinketData(ETrinketType type)
{
	if (trinket_table_)
	{
		return *trinket_table_->FindRow<FTrinketData>(*TrinketEnumToString(type), TEXT(""));
	}
	return *trinket_table_->FindRow<FTrinketData>(*TrinketEnumToString(ETrinketType::Empty), TEXT(""));
}

FString UEquipManager::TrinketEnumToString(ETrinketType trinket_type)
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

FWeaponData UEquipManager::GetWeaponData(EWeaponType type)
{
	if (weapon_table_)
	{
		return *weapon_table_->FindRow<FWeaponData>(*WeaponEnumToString(type), TEXT(""));
	}
	return *weapon_table_->FindRow<FWeaponData>(*WeaponEnumToString(EWeaponType::Empty), TEXT(""));
}

FString UEquipManager::WeaponEnumToString(EWeaponType weapon_type)
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

FPassiveSkillData UEquipManager::GetPassiveSkillData(EPassiveSkillType type)
{
	if (passive_skill_table_)
	{
		return *passive_skill_table_->FindRow<FPassiveSkillData>(*PassiveSkillEnumToString(type), TEXT(""));
	}
	return *passive_skill_table_->FindRow<FPassiveSkillData>(*PassiveSkillEnumToString(EPassiveSkillType::Empty), TEXT(""));
}

FString UEquipManager::PassiveSkillEnumToString(EPassiveSkillType weapon_type)
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
