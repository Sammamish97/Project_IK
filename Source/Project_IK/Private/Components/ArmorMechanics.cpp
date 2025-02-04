/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.1.2025
Summary : Source file for the ArmorMechanics.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Components/ArmorMechanics.h"

#include "Abilities/EquipmentSkills/EquipmentSkillBase.h"
#include "Characters/HeroBase.h"
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

	armor_manager_cache_ = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GetArmorManager();
	hero_cache_ = Cast<AHeroBase>(GetOwner());
}

FArmorData UArmorMechanics::GetEquippedArmorData()
{
	return equipped_armor_data_;
}

//TODO: 아머를 장착하는 부분과 delegate를 bind하는 부분을 분리해야 한다. 장착은 inventory에서 할 수 있지만, inventory에서 장착했을 때 delegate를 bind할 필요는 없기 때문.
//TODO: Delegate를 bind하는 시점은, hero가 spawn되는 시점이다.
void UArmorMechanics::EquipArmor(EArmorType type)
{
	equipped_armor_data_ = armor_manager_cache_->GetArmorData(type);
	if (equipped_armor_data_.has_skill)
	{
		auto armor_equipment_skill = GetWorld()->SpawnActor<AEquipmentSkillBase>(equipped_armor_data_.equipment_skill_class);
		armor_equipment_skill->AttachToActor(hero_cache_, FAttachmentTransformRules::KeepRelativeTransform);
		armor_equipment_skill->InitEquipmentSkill(hero_cache_	);
	}
}

void UArmorMechanics::UnEquipArmor()
{
	equipped_armor_data_ = armor_manager_cache_->GetArmorData(EArmorType::Empty);
}