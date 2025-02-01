/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.1.2025
Summary : Source file for the ArmorMechanics.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Components/ArmorMechanics.h"


// Sets default values for this component's properties
UArmorMechanics::UArmorMechanics()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	FString armor_data_path = TEXT("/Script/Engine.DataTable'/Game/Resources/IK_Armor_Data.IK_Armor_Data'");
	static ConstructorHelpers::FObjectFinder<UDataTable> dt_armor_data(*armor_data_path);
	if (dt_armor_data.Succeeded() == false)
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance has failed to load a dp file data (IK_Proto_Drone_Plugin_Data)"));
	}
	armor_table_= dt_armor_data.Object;
}

// Called when the game starts
void UArmorMechanics::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UArmorMechanics::TestSkill_1_Prepare()
{
	//Prepare를 통해 event와 bind하거나 특수효과에 준비가 필요하다면 준비한다.
}

FDamageData UArmorMechanics::TestSkill_1(FDamageData dmg_input)
{
	dmg_input.damage_ -= 3;
	return dmg_input;
}

void UArmorMechanics::TestSkill_1_Terminate()
{
	//Terminate를 통해 bind해준 함수를 해제하거나 소멸시킬 것들을 소멸시킨다.
}

void UArmorMechanics::EquipArmor()
{
	//TODO: 만약 event에 bind를 해야하는 특수효과면, 여기서 bind한다.
	if (equipped_armor_data_.type_ != EArmorType::Empty || equipped_armor_data_.has_skill_ == true)
	{
		
	}
}

void UArmorMechanics::UnEquipArmor()
{
	//TODO: 만약 event에 bind를 해야하는 특수효과면, 여기서 bind를 해제한다.
}

void UArmorMechanics::ParseArmorData(EArmorType type)
{
	if (armor_table_)
	{
		equipped_armor_data_ = *armor_table_->FindRow<FArmorData>(*EnumToString(type), TEXT(""));
	}
	equipped_armor_data_ = *armor_table_->FindRow<FArmorData>(*EnumToString(EArmorType::Empty), TEXT(""));
}

FArmorData UArmorMechanics::GetArmorData()
{
	return equipped_armor_data_;
}

FString UArmorMechanics::EnumToString(EArmorType armor_type)
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