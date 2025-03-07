/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.5.2025
Summary : Source file for the Random damage increase skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/EquipSkills/RandDmgIncreaseSkill.h"
#include "Characters/HeroBase.h"
void URandDmgIncreaseSkill::InitEquipmentSkill(AActor* hero_ref)
{
	Super::InitEquipmentSkill(hero_ref);
	bound_target_ = EHeroEvent::OnFire;
	auto& delegate_array = hero_cache_->hero_dmg_event_map_.FindOrAdd(bound_target_);
	delegate_array.AddDefaulted();
	delegate_array.Last().BindUObject(this, &URandDmgIncreaseSkill::OnEquipmentSkill);
}

FDamageData URandDmgIncreaseSkill::OnEquipmentSkill(FDamageData dmg_data)
{
	dmg_data.atk_base_dmg += FMath::RandRange(1, 5);
	return dmg_data;
}
