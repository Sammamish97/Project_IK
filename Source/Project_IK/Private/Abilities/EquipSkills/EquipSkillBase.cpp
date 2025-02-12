/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.5.2025
Summary : Source file for the EquipSkillBase.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/EquipSkills/EquipSkillBase.h"
#include "Characters/HeroBase.h"

void UEquipSkillBase::InitEquipmentSkill(AActor* hero_ref)
{
	hero_cache_ = Cast<AHeroBase>(hero_ref);
}

FDamageData UEquipSkillBase::OnEquipmentSkill(FDamageData dmg_data)
{
	return dmg_data;
}

