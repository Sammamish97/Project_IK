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
	Super::ApplyBuff(target);
	target_cache_->ApplyStatusBuff(buff_type_, first_buff_status_data_);
	if (first_buff_status_data_.is_permanent_)
	{
		target_cache_->AddBuffUI(buff_type_, display_data_);
	}
	else
	{
		target_cache_->AddBuffUI(buff_type_, display_data_, first_buff_status_data_.duration_);
	}
	
	target_cache_->ApplyStatusBuff(buff_type_, second_buff_status_data_);
	if (second_buff_status_data_.is_permanent_)
	{
		target_cache_->AddBuffUI(buff_type_, display_data_);
	}
	else
	{
		target_cache_->AddBuffUI(buff_type_, display_data_, second_buff_status_data_.duration_);
	}
}

void UBF_TwoStatusBuff::RemoveBuff(AUnit* target)
{
	Super::RemoveBuff(target);
	target_cache_->RemoveBuff(buff_type_);
	target_cache_->RemoveBuffUI(buff_type_);
}