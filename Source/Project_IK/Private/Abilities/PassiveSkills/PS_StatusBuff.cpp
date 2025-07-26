/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.21.2025
Summary : Header file for the status buff passive skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/PassiveSkills/PS_StatusBuff.h"

#include "Characters/HeroBase.h"

UPS_StatusBuff::UPS_StatusBuff()
{
	buff_status_data_.duration_ = 0.f;
	buff_status_data_.is_percentage_ = false;
	buff_status_data_.is_permanent_ = true;
}

void UPS_StatusBuff::InitPassiveSkill(AActor* hero_ref, const FPassiveSkillData& skill_data)
{
	Super::InitPassiveSkill(hero_ref, skill_data);
	auto casted_hero = Cast<AHeroBase>(hero_ref);

	casted_hero->ApplyStatusBuff(buff_type_, buff_status_data_);
	//casted_hero->AddBuffUI({skill_data_.item_data_, buff_type_, buff_status_data_.duration_, buff_status_data_.is_permanent_ });
}
