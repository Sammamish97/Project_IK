/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.28.2025
Summary : Source file for the Composed passive skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/Buffs/BF_Composed.h"

#include "Characters/Unit.h"
#include "Components/CharacterStatComponent.h"

void UBF_Composed::ApplyBuff(AUnit* target)
{
	Super::ApplyBuff(target);
	float hp_ratio = target->GetCharacterStat()->GetHPRatio();
	float buff_amount;
	if (hp_ratio <= max_hp_ratio_)
	{
		buff_amount = max_dodge_rate_;
	}
	else
	{
		float alpha = (max_hp_ratio_ - hp_ratio) / (max_hp_ratio_ - min_hp_ratio_);
		buff_amount = FMath::Lerp(min_dodge_rate_, max_dodge_rate_, alpha);
	}
	dodge_status_.value_ = buff_amount;
	target->ApplyStatusBuff(EBuffType::Composure, dodge_status_);
	target->AddBuffUI(EBuffType::Composure, display_data_);
}

void UBF_Composed::RemoveBuff(AUnit* target)
{
	Super::RemoveBuff(target);
	target->RemoveBuff(EBuffType::Composure);
	target->RemoveBuffUI(EBuffType::Composure);
}
