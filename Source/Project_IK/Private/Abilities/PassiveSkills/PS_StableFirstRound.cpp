/******************************************************************************
Copyright(C) 2025
Author: Sinil Kang (rtd99062@gmail.com)
Creation Date : 5.2.2025
Summary : Source file for the stable first round passive skill.
					It gives high critical rate buffs on the first shot in megazines.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/PassiveSkills/PS_StableFirstRound.h"

#include "Abilities/Buffs/BuffHandler.h"
#include "Subsystems/DelegateBridgeSubsystem.h"
#include "Abilities/Buffs/BuffHandler.h"

void UPS_StableFirstRound::InitPassiveSkill(AActor* hero_ref, const FPassiveSkillData& skill_data)
{
	Super::InitPassiveSkill(hero_ref, skill_data);
	buff_ = NewObject<UBuffHandler>(this, buff_class_);
	buff_->ApplyBuff(Cast<AUnit>(hero_ref));
}