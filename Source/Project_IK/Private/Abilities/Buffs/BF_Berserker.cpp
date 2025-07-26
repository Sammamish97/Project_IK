/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.23.2025
Summary : Source file for Berserker buff.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/Buffs/BF_Berserker.h"

#include "Characters/Unit.h"

void UBF_Berserker::ApplyBuff(AUnit* target)
{
	Super::ApplyBuff(target);

	target_cache_->ApplyStatusBuff(buff_type_, atk_speed_stat_data_);
	target_cache_->ApplyStatusBuff(buff_type_, vamp_stat_data_);
	target_cache_->AddBuffUI(buff_type_, display_data_);
}

void UBF_Berserker::RemoveBuff(AUnit* target)
{
	Super::RemoveBuff(target);
	target_cache_->RemoveBuff(buff_type_);
	target_cache_->RemoveBuffUI(buff_type_);
}
