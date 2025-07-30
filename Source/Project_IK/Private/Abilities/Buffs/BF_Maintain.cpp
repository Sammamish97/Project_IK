/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.24.2025
Summary : Source file for one Maintain buff.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/Buffs/BF_Maintain.h"

#include "Characters/Unit.h"

void UBF_Maintain::ApplyBuff(AUnit* target)
{
	target_cache_ = target;
	target->AcquireShield(shield_amount_, 5.f);
	FTimerDelegate heal_del = FTimerDelegate::CreateUObject(this, &UBF_Maintain::Heal);
	GetWorld()->GetTimerManager().SetTimer(heal_timer_handle_, heal_del, 0.5f, true);
}

void UBF_Maintain::RemoveBuff(AUnit* target)
{
	GetWorld()->GetTimerManager().ClearTimer(heal_timer_handle_);
	target->RemoveBuffUI(buff_type_);
}

void UBF_Maintain::Heal()
{
	if (auto target = target_cache_.Get())
	{
		target->Heal(heal_per_half_sec_);
	}
}
