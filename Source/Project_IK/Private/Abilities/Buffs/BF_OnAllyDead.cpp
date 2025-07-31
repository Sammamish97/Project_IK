/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.31.2025
Summary : Source file for one Ally Dead buff/Debuff.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/Buffs/BF_OnAllyDead.h"

#include "Kismet/GameplayStatics.h"
#include "Characters/Unit.h"
#include "Subsystems/DelegateBridgeSubsystem.h"

void UBF_OnAllyDead::ApplyBuff(AUnit* target)
{
	target_cache_ = target;
	auto world_cache = GetWorld();
	
	TArray<AActor*> all_allies_;
	UGameplayStatics::GetAllActorsOfClass(world_cache, ally_class, all_allies_);
	
	for (const auto& elem : all_allies_)
	{
		GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnUnitEvent(elem, EUnitEvent::OnDie, this, &UBF_OnAllyDead::OnAllyDie);
	}
	target->AddBuffUI(EBuffType::OnAllyDead, display_data_);
}

void UBF_OnAllyDead::OnAllyDie()
{
	if (auto target = target_cache_.Get())
	{
		dead_ally_ += 1;
		FBuffStatusData atk_buff = {ECharacterStatType::AttackPower, dead_ally_ * atk_power_buff_per_ally_die_, true, true};
		FBuffStatusData ats_buff = {ECharacterStatType::AttackPower, dead_ally_ * atk_power_buff_per_ally_die_, true, true};
		target->ApplyStatusBuff(EBuffType::OnAllyDead, atk_buff);
		target->ApplyStatusBuff(EBuffType::OnAllyDead, ats_buff);
	}
}
