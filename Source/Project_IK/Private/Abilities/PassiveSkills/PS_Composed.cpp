/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.21.2025
Summary : Source file for the Composure passive skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/PassiveSkills/PS_Composed.h"

#include "Abilities/Buffs/BuffHandler.h"
#include "Characters/Unit.h"
#include "Subsystems/DelegateBridgeSubsystem.h"

void UPS_Composed::InitPassiveSkill(AActor* hero_ref, const FPassiveSkillData& skill_data)
{
	Super::InitPassiveSkill(hero_ref, skill_data);
	if (AUnit* unit = Cast<AUnit>(hero_ref))
	{
		hero_ref->GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnHPChanged(unit->GetCharacterStat(), this, &UPS_Composed::OnHPChanged);
	}
	buff_ = NewObject<UBuffHandler>(this, buff_class_);
}

void UPS_Composed::OnHPChanged(float hp_ratio)
{
	if (hp_ratio <= trigger_hp_ratio_)
	{
		if (is_buff_applied_ == false)
		{
			buff_->ApplyBuff(Cast<AUnit>(hero_cache_));
			is_buff_applied_ = true;
		}
	}
	else
	{
		if (is_buff_applied_ == true)
		{
			buff_->RemoveBuff(Cast<AUnit>(hero_cache_));
			is_buff_applied_ = false;
		}
	}
}