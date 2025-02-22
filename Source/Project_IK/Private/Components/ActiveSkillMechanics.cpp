/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.22.2025
Summary : Source file for Active Skill Mechanics.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/#include "Components/ActiveSkillMechanics.h"

#include "Abilities/ActiveSkills/ActiveSkillBase.h"
#include "Characters/HeroBase.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/DataTableManager.h"
#include "WorldSettings/IKGameInstance.h"


// Sets default values for this component's properties
UActiveSkillMechanics::UActiveSkillMechanics()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UActiveSkillMechanics::BeginPlay()
{
	Super::BeginPlay();

	hero_cache_ = Cast<AHeroBase>(GetOwner());
	equip_manager_cache_ = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GetEquipManager();
}

FActiveSkillData UActiveSkillMechanics::GetEquippedActiveSkill()
{
	return equipped_active_skill_data_;
}

void UActiveSkillMechanics::EquipActiveSkill(EActiveSkillType type)
{
	equipped_active_skill_data_ = equip_manager_cache_->GetActiveSkillData(type);
	active_skill_cache_ = NewObject<UActiveSkillBase>(this, equipped_active_skill_data_.active_skill_class);
	active_skill_cache_->InitActiveSkill(hero_cache_);
}

void UActiveSkillMechanics::UnEquipActiveSkill()
{
	equipped_active_skill_data_ = equip_manager_cache_->GetActiveSkillData(EActiveSkillType::Empty);
}
