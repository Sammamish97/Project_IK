/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.28.2025
Summary : Source file for the Executioner passive skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/Buffs/BF_Executioner.h"
#include "Abilities/Buffs/BuffHandler.h"
#include "Subsystems/DelegateBridgeSubsystem.h"

void UBF_Executioner::ApplyBuff(AUnit* target)
{
	target_cache_ = target;
	GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnUnitEvent(target, EUnitEvent::OnEliminate, this, &UBF_Executioner::OnEliminate);
}

void UBF_Executioner::OnEliminate()
{
	if (auto target = target_cache_.Get())
	{
		if (auto casted_hero = Cast<AHeroBase>(target))
		{
			casted_hero->ReduceActiveSkillCoolDown(1.f);
			casted_hero->ApplyStatusBuff(buff_type_, buff_status_data_);
			casted_hero->AddBuffUI(buff_type_, thumbnail_, buff_status_data_.duration_);
		}
	}
}
