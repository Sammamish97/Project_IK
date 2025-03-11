/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.5.2025
Summary : Source file for the Fixed damage reduce skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/EquipSkills/FixedDmgReduceSkill.h"
#include "Characters/HeroBase.h"

void UFixedDmgReduceSkill::InitEquipmentSkill(AActor* hero_ref)
{
	Super::InitEquipmentSkill(hero_ref);
	bound_target_ = EHeroEvent::OnHitAfterCalc;
	//hero_cache_->hero_dmg_event_map_.FindOrAdd(bound_target_).BindUObject(this, &UFixedDmgReduceSkill::OnEquipmentSkill);
	auto& delegate_array = hero_cache_->hero_dmg_event_map_.FindOrAdd(bound_target_);
	delegate_array.AddDefaulted();
	delegate_array.Last().BindUObject(this, &UFixedDmgReduceSkill::OnEquipmentSkill);
}

FDamageData UFixedDmgReduceSkill::OnEquipmentSkill(FDamageData dmg_data)
{
	dmg_data.atk_base_dmg -= 3;
	return dmg_data;
}
