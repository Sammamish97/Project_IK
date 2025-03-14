/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.5.2025
Summary : Source file for the EquipMechanics.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Components/EquipMechanics.h"

#include "Abilities/EquipSkills/EquipSkillBase.h"
#include "Characters/HeroBase.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/DataTableManager.h"
#include "WorldSettings/IKGameInstance.h"

// Sets default values for this component's properties
UEquipMechanics::UEquipMechanics()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UEquipMechanics::BeginPlay()
{
	Super::BeginPlay();
	hero_cache_ = Cast<AHeroBase>(GetOwner());
	data_table_cache_ = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GetDataTableManager();
}

FArmorData UEquipMechanics::GetEquippedArmorData()
{
	return equipped_armor_data_;
}

void UEquipMechanics::EquipArmor(EArmorType type)
{
	equipped_armor_data_ = data_table_cache_->GetArmorData(type);
	if (equipped_armor_data_.has_skill)
	{
		//TODO: 특수효과는 전투 레벨이 끝나면 필요 없기에 전투 레벨이 끝남과 함께 영웅과 함꼐 삭제되리라 밑고 일단 따로 저장/삭제 로직을 넣지 않았다.
		auto equip_skill = NewObject<UEquipSkillBase>(this, equipped_armor_data_.equipment_skill_class);
		equip_skill->InitEquipmentSkill(hero_cache_);

		equip_skill->MarkAsGarbage();
	}
}

void UEquipMechanics::UnEquipArmor()
{
	equipped_armor_data_ = data_table_cache_->GetArmorData(EArmorType::Empty);
}

FTrinketData UEquipMechanics::GetEquippedTrinketData()
{
	return equipped_trinket_data_;
}

void UEquipMechanics::EquipTrinket(ETrinketType type)
{
	equipped_trinket_data_ = data_table_cache_->GetTrinketData(type);
	if (equipped_trinket_data_.has_skill)
	{
		//TODO: 특수효과는 전투 레벨이 끝나면 필요 없기에 전투 레벨이 끝남과 함께 영웅과 함꼐 삭제되리라 밑고 일단 따로 저장/삭제 로직을 넣지 않았다.
		//TODO: 추후 영웅의 제거와 함께 자동으로 삭제되는지 테스트 해봐야 한다.
		NewObject<UEquipSkillBase>(this, equipped_trinket_data_.equipment_skill_class)->InitEquipmentSkill(hero_cache_);
	}
}

void UEquipMechanics::UnEquipTrinket()
{
	equipped_armor_data_ = data_table_cache_->GetArmorData(EArmorType::Empty);
	equipped_trinket_data_ = data_table_cache_->GetTrinketData(ETrinketType::Empty);
}
