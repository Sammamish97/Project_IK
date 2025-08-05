/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.31.2025
Summary : Source file for Display Only buff.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/Buffs/BF_DisplayOnly.h"
#include "Characters/Unit.h"

void UBF_DisplayOnly::ApplyBuff(AUnit* target)
{
	Super::ApplyBuff(target);
	if (is_permanent_)
	{
		target->AddBuffUI(buff_type_, display_data_);
	}
	else
	{
		target->AddBuffUI(buff_type_, display_data_, duration_);
	}
}

void UBF_DisplayOnly::RemoveBuff(AUnit* target)
{
	Super::RemoveBuff(target);
	target->RemoveBuffUI(buff_type_);
}
