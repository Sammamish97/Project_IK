/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.09.2025
Summary : Source file for Passive Skill Mechanics.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Components/PassiveSkillMechanics.h"

#include "Abilities/PassiveSkills/PassiveSkillBase.h"
#include "Characters/HeroBase.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/DataTableManager.h"
#include "WorldSettings/IKGameInstance.h"

void UPassiveSkillMechanics::BeginPlay()
{
	Super::BeginPlay();
	hero_cache_ = Cast<AHeroBase>(GetOwner());
	data_table_cache_ = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GetDataTableManager();
}

FPassiveSkillData UPassiveSkillMechanics::GetEquippedPassiveSkillData()
{
	return equipped_passive_skill_data_;
}

void UPassiveSkillMechanics::EquipPassiveSkill(const FPassiveSkillData& skill_data)
{
	equipped_passive_skill_data_ = skill_data;
	passive_skill_cache_ = NewObject<UPassiveSkillBase>(this, equipped_passive_skill_data_.passive_skill_class);
}

void UPassiveSkillMechanics::InitPassiveSkill()
{
	if (passive_skill_cache_)
	{
		passive_skill_cache_->InitPassiveSkill(hero_cache_, equipped_passive_skill_data_);
	}
}

void UPassiveSkillMechanics::UnEquipPassiveSkill()
{
	equipped_passive_skill_data_ = data_table_cache_->GetPassiveSkillData(EPassiveSkillType::INVALID);
}