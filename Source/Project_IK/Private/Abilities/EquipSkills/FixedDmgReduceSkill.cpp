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
	hero_cache_->BindDamageEvent(bound_target_, this, &UFixedDmgReduceSkill::OnEquipmentSkill);
}

FDamageData UFixedDmgReduceSkill::OnEquipmentSkill(FDamageData dmg_data)
{
	dmg_data.atk_base_dmg = FMath::Max(0.f, dmg_data.atk_base_dmg - 3.f);
	return dmg_data;
}
