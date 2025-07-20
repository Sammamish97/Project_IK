/******************************************************************************
Copyright(C) 2025
Author: Sinil Kang (rtd99062@gmail.com)
Creation Date : 5.2.2025
Summary : Source file for the stable first round passive skill.
					It gives high critical rate buffs on the first shot in megazines.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/PassiveSkills/PS_StableFirstRound.h"

#include "Subsystems/DelegateBridgeSubsystem.h"

void UPS_StableFirstRound::InitPassiveSkill(AActor* hero_ref, const FPassiveSkillData& skill_data)
{
	Super::InitPassiveSkill(hero_ref, skill_data);

	hero_ref->GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnCriticalRateCalculation(hero_ref, this, &UPS_StableFirstRound::CriticalRateBuffIfReloaded);
	hero_ref->GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnUnitEvent(hero_ref, EUnitEvent::OnReload, this, &UPS_StableFirstRound::CheckHasReloaded);
}

void UPS_StableFirstRound::CriticalRateBuffIfReloaded(float& critical_rate)
{
	if (is_first_shot_)
	{
		critical_rate += 100.f;
		is_first_shot_ = false;
	}
}

void UPS_StableFirstRound::CheckHasReloaded()
{
	is_first_shot_ = true;
}
