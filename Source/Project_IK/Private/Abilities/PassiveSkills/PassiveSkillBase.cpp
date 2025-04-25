/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.5.2025
Summary : Source file for the EquipSkillBase.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/PassiveSkills/PassiveSkillBase.h"
#include "Characters/HeroBase.h"

void UPassiveSkillBase::InitEquipmentSkill(AActor* hero_ref)
{
}

FDamageData UPassiveSkillBase::OnEquipmentSkill(FDamageData dmg_data)
{
	return dmg_data;
}

