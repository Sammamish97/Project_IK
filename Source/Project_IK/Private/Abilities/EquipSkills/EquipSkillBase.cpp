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

//이 함수는 자기 자신이 bind된 hero의 delegate를 unbind해주는 역할을 한다.
//그러나 hero의 delegate는 전투가 끝나고 destroy될 때 전부 unbind되고, 전투 중 delegate가 교체될 일이 없으므로 이상적으로 이 함수가 불릴 일은 없어야 한다.
void UEquipSkillBase::ClearEquipmentSkill()
{
	if (hero_cache_->hero_dmg_event_map_[bound_target_].IsBound())
	{
		hero_cache_->hero_dmg_event_map_[bound_target_].Unbind();
	}
}

