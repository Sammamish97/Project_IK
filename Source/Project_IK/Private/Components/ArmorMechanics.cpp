/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.1.2025
Summary : Source file for the ArmorMechanics.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Components/ArmorMechanics.h"
#include "WorldSettings/IKGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/ArmorManager.h"


// Sets default values for this component's properties
UArmorMechanics::UArmorMechanics()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UArmorMechanics::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

FDamageData UArmorMechanics::TestSkill_1(UArmorMechanics* target, FDamageData dmg_input)
{
	dmg_input.damage -= 3;
	return dmg_input;
}

void UArmorMechanics::TestSkill_1_Prepare()
{
	//Prepare를 통해 event와 bind하거나 특수효과에 준비가 필요하다면 준비한다.
	OnArmorHitFunction = &UArmorMechanics::TestSkill_1;
}


void UArmorMechanics::TestSkill_1_Terminate()
{
	//Terminate를 통해 bind해준 함수를 해제하거나 소멸시킬 것들을 소멸시킨다.
	OnArmorHitFunction = nullptr;
}

FArmorData UArmorMechanics::GetEquippedArmorData()
{
	return equipped_armor_data_;
}

void UArmorMechanics::EquipArmor(EArmorType type)
{
	if (UIKGameInstance* instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		equipped_armor_data_ = instance->GetArmorManager()->GetArmorData(type);
	}
}

void UArmorMechanics::UnEquipArmor()
{
	if (UIKGameInstance* instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld())))
	{
		equipped_armor_data_ = instance->GetArmorManager()->GetArmorData(EArmorType::Empty);
	}
	OnArmorHitFunction = nullptr;
}
