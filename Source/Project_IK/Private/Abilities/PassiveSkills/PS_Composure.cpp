/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.21.2025
Summary : Source file for the Composure passive skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/PassiveSkills/PS_Composure.h"

#include "Characters/Unit.h"
#include "Subsystems/DelegateBridgeSubsystem.h"

void UPS_Composure::InitPassiveSkill(AActor* hero_ref, const FPassiveSkillData& skill_data)
{
	Super::InitPassiveSkill(hero_ref, skill_data);
	AUnit* unit = Cast<AUnit>(hero_ref);
	if (unit)
	{
		hero_ref->GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnHPChanged(unit->GetCharacterStat(), this, &UPS_Composure::OnHPChanged);
	}
}

void UPS_Composure::OnHPChanged(float hp_ratio)
{
	if (hp_ratio < min_hp_ratio_)
	{
		if (hp_ratio <= max_hp_ratio_)
		{
			ApplyBuff(max_dodge_rate_);
		}
		else
		{
			float alpha = (max_hp_ratio_ - hp_ratio) / (max_hp_ratio_ - min_hp_ratio_);
			float buff_amount = FMath::Lerp(min_dodge_rate_, max_dodge_rate_, alpha);
			ApplyBuff(buff_amount);
		}
	}
	else
	{
		RemoveBuff();
	}
}

void UPS_Composure::ApplyBuff(float buff_amount)
{
	auto buff_status = FBuffStatusData(ECharacterStatType::EvasionRate, buff_amount, false, true);
	Cast<AHeroBase>(hero_cache_)->ApplyBuff(EBuffType::Composure, buff_status);
	Cast<AHeroBase>(hero_cache_)->AddBuffUI({skill_data_.item_data_, EBuffType::Composure, 0.f, true});
}

void UPS_Composure::RemoveBuff()
{
	Cast<AHeroBase>(hero_cache_)->RemoveBuff(EBuffType::Composure);
	Cast<AHeroBase>(hero_cache_)->RemoveBuffUI(EBuffType::Composure);
}
