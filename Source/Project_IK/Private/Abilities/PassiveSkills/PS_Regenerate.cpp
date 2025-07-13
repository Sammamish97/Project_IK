/******************************************************************************
Copyright(C) 2025
Author: Sinil Kang (rtd99062@gmail.com)
Creation Date : 4.26.2025
Summary : Source file for the regenerate passive skill.
					It restores skill owner's hit points.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/PassiveSkills/PS_Regenerate.h"

#include "Characters/Unit.h"

void UPS_Regenerate::InitPassiveSkill(AActor* hero_ref, const FPassiveSkillData& skill_data)
{
	Super::InitPassiveSkill(hero_ref, skill_data);
	hero_ref->GetWorld()->GetTimerManager().SetTimer(regenerate_timer_handler_, this, &UPS_Regenerate::Regenerate, regenerate_intervals_, true);
}

void UPS_Regenerate::Regenerate()
{
	AActor* hero = hero_cache_.Get();
	if (hero)
	{
		AUnit* unit = Cast<AUnit>(hero);

		unit->Heal(restore_hit_points_amount_);
	}
}
