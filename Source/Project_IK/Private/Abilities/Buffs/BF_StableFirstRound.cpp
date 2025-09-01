/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.28.2025
Summary : Source file for stable first round passive skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/Buffs/BF_StableFirstRound.h"

#include "Subsystems/DelegateBridgeSubsystem.h"

void UBF_StableFirstRound::ApplyBuff(AUnit* target)
{
	Super::ApplyBuff(target);
	auto world_cache = GetWorld();
	world_cache->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnCriticalRateCalculation(target, this, &UBF_StableFirstRound::CritBuffOnReload);
	world_cache->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnUnitEvent(target, EUnitEvent::OnReload, this, &UBF_StableFirstRound::OnReload);
	target->AddBuffUI(buff_type_);
}

void UBF_StableFirstRound::OnReload()
{
	is_first_shot_ = true;
}

void UBF_StableFirstRound::CritBuffOnReload(float& critical_rate)
{
	if (is_first_shot_)
	{
		critical_rate += 100.f;
		is_first_shot_ = false;
	}
}
