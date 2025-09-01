/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.28.2025
Summary : Source file for one status buff.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/Buffs/BF_TwoStatusBuff.h"

#include "Characters/Unit.h"

void UBF_TwoStatusBuff::ApplyBuff(AUnit* target)
{
	target->ApplyStatusBuff(buff_type_, first_buff_status_data_);
	if (first_buff_status_data_.is_permanent_)
	{
		target->AddBuffUI(buff_type_);
	}
	else
	{
		target->AddBuffUI(buff_type_, first_buff_status_data_.duration_);
	}
	
	target->ApplyStatusBuff(buff_type_, second_buff_status_data_);
	if (second_buff_status_data_.is_permanent_)
	{
		target->AddBuffUI(buff_type_);
	}
	else
	{
		target->AddBuffUI(buff_type_, second_buff_status_data_.duration_);
	}
}

void UBF_TwoStatusBuff::RemoveBuff(AUnit* target)
{
	if (IsValid(target))
	{
		target->RemoveBuff(buff_type_);
		target->RemoveBuffUI(buff_type_);
	}
}