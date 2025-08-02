/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 07.28.2025
Summary : Source file for a buff that applies to a hero that has been dead.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/Buffs/BF_MultipleStatusBuff.h"

#include "Characters/Unit.h"

void UBF_MultipleStatusBuff::ApplyBuff(AUnit* target)
{
	Super::ApplyBuff(target);

	for (const FBuffStatusData& data : buff_stat_data_)
	{
		target->ApplyStatusBuff(buff_type_, data);
	}
	target->AddBuffUI(buff_type_, display_data_);
}
