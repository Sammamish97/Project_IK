/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.22.2025
Summary : Source file for encourage buff.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/Buffs/BF_Encourage.h"
#include "Characters/Unit.h"

void UBF_Encourage::ApplyBuff(AUnit* target)
{
	Super::ApplyBuff(target);
	atk_power_stat_data_.duration_ = duration_;
	skill_power_stat_data_.duration_ = duration_;
	
	target_cache_->ApplyStatusBuff(buff_type_, atk_power_stat_data_);
	target_cache_->ApplyStatusBuff(buff_type_, skill_power_stat_data_);
	target_cache_->AddBuffUI(buff_type_, display_data_, duration_);
}
