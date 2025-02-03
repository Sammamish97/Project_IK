/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.02.2025
Summary : Source file for ArmorManager.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Managers/ArmorManager.h"
#include "Abilities/ArmorSkillCluster.h"

UArmorManager::UArmorManager()
{
	FString armor_data_path = TEXT("/Script/Engine.DataTable'/Game/Resources/IK_Armor_Data.IK_Armor_Data'");
	static ConstructorHelpers::FObjectFinder<UDataTable> dt_armor_data(*armor_data_path);
	if (dt_armor_data.Succeeded() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance has failed to load a armor file data (IK_Armor_Data)"));
	}
	armor_table_= dt_armor_data.Object;
}

void UArmorManager::InitArmorManager()
{
	InitArmorSkillMap();
}

void UArmorManager::InitArmorSkillMap()
{
	//TODO: 여기서 특수 효과를 가진 방어구의 스킬을 직접 enum type과 함께 map에 넣어줘야 한다.
	armor_skill_map_.Add(EArmorType::TestSkillArmor, ArmorSkillCluster::TestSkill_1);
}

FArmorData UArmorManager::GetArmorData(EArmorType type)
{
	if (armor_table_)
	{
		return *armor_table_->FindRow<FArmorData>(*EnumToString(type), TEXT(""));
	}
	return *armor_table_->FindRow<FArmorData>(*EnumToString(EArmorType::Empty), TEXT(""));
}

const ArmorSkillMap& UArmorManager::GetArmorSkillMap() const
{
	return armor_skill_map_;
}

FString UArmorManager::EnumToString(EArmorType armor_type)
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
