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

void UPassiveSkillMechanics::BeginPlay()
{
	Super::BeginPlay();
	hero_cache_ = Cast<AHeroBase>(GetOwner());
	passive_skills_.Init(nullptr, 3);
	equipped_passive_skill_data_.Init(FPassiveSkillData(), 3);
}

void UPassiveSkillMechanics::EquipPassiveSkill(const FPassiveSkillData& skill_data, int32 idx)
{
	equipped_passive_skill_data_[idx] = skill_data;
	passive_skills_[idx] = NewObject<UPassiveSkillBase>(this, equipped_passive_skill_data_[idx].passive_skill_class);
}

void UPassiveSkillMechanics::InitPassiveSkill()
{
	for (int32 i = 0; i < 3; i++)
	{
		if (passive_skills_[i] != nullptr)
		{
			passive_skills_[i]->InitPassiveSkill(hero_cache_, equipped_passive_skill_data_[i]);
		}
	}
}
	
void UPassiveSkillMechanics::UnEquipPassiveSkill(int32 idx)
{
	passive_skills_[idx] = nullptr;
	equipped_passive_skill_data_[idx] = FPassiveSkillData();
}