/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.28.2025
Summary : Source file for encourage.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/Buffs/BF_Encourage.h"

#include "Characters/Unit.h"

void UBF_Encourage::ApplyBuff(AUnit* target)
{
	Super::ApplyBuff(target);
	target->AcquireShield(shield_amount_, first_buff_status_data_.duration_);
}
