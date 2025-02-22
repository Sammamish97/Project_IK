/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.09.2025
Summary : Source file for Passive Skill Mechanics.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Components/PassiveSkillMechanics.h"

#include "Characters/HeroBase.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/DataTableManager.h"
#include "WorldSettings/IKGameInstance.h"


// Sets default values for this component's properties
UPassiveSkillMechanics::UPassiveSkillMechanics()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UPassiveSkillMechanics::BeginPlay()
{
	Super::BeginPlay();
	hero_cache_ = Cast<AHeroBase>(GetOwner());
	equip_manager_cache_ = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GetEquipManager();
}

FPassiveSkillData UPassiveSkillMechanics::GetEquippedPassiveSkillData()
{
	return equipped_passiev_skill_data_;
}

void UPassiveSkillMechanics::EquipPassiveSkill(EPassiveSkillType type)
{
	equipped_passiev_skill_data_ = equip_manager_cache_->GetPassiveSkillData(type);
	passive_skill_cache_ = NewObject<UEquipSkillBase>(this, equipped_passiev_skill_data_.passive_skill_class);
	passive_skill_cache_->InitEquipmentSkill(hero_cache_);
}

void UPassiveSkillMechanics::UnEquipPassiveSkill()
{
	equipped_passiev_skill_data_ = equip_manager_cache_->GetPassiveSkillData(EPassiveSkillType::Empty);
}
