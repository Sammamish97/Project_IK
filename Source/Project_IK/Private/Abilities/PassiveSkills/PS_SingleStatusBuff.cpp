/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.28.2025
Summary : Source file for the single status buff passive skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/PassiveSkills/PS_SingleStatusBuff.h"

#include "Abilities/Buffs/BuffHandler.h"
#include "Characters/Unit.h"

void UPS_SingleStatusBuff::InitPassiveSkill(AActor* hero_ref, const FPassiveSkillData& skill_data)
{
	Super::InitPassiveSkill(hero_ref, skill_data);
	buff_ = NewObject<UBuffHandler>(this, buff_class_);
	buff_->ApplyBuff(Cast<AUnit>(hero_ref));
}
