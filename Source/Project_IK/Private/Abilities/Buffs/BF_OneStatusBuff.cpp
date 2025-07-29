/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.22.2025
Summary : Source file for one status buff.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/Buffs/BF_OneStatusBuff.h"

#include "Characters/Unit.h"

void UBF_OneStatusBuff::ApplyBuff(AUnit* target)
{
	Super::ApplyBuff(target);
	target_cache_->ApplyStatusBuff(buff_type_, buff_status_data_);
	if (buff_status_data_.is_permanent_)
	{
		target_cache_->AddBuffUI(buff_type_, display_data_);
	}
	else
	{
		target_cache_->AddBuffUI(buff_type_, display_data_, buff_status_data_.duration_);
	}
}

void UBF_OneStatusBuff::RemoveBuff(AUnit* target)
{
	Super::RemoveBuff(target);
	target_cache_->RemoveBuff(buff_type_);
	target_cache_->RemoveBuffUI(buff_type_);
}