/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.22.2025
Summary : Source file for the Instant Repair Support SKill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Abilities/SupportSkills/SP_InstantRepair.h"

#include "Characters/HeroBase.h"
#include "Components/CharacterStatComponent.h"

USP_InstantRepair::USP_InstantRepair()
{
	target_param_ = FTargetParameters(ETargetingMode::Actor, ETargetType::Allies, 1000.f);
	cool_time_ = 2.f;
	cost_ = 3.f;
}

bool USP_InstantRepair::ActivateSkill(const FTargetResult& target_result)
{
	EBuffType type = EBuffType::InstantRepair;
	FBuffStatusData status_data = FBuffStatusData(ECharacterStatType::AttackSpeed, 2.0f, true, false, 3.f);
	
	if(target_result.target_actors_[0])
	{
		if (AHeroBase* target_hero = Cast<AHeroBase>(target_result.target_actors_[0]))
		{
			target_hero->ApplyBuff(type, status_data);
			target_hero->Heal(300.f);
			target_hero->AddBuffUI(FBuffUIData(FText::FromString("InstantRepair"), type, nullptr, 1.f, false, FText::FromString("Test Instnatn Repair")));
		}
	}
	return Super::ActivateSkill(target_result);
}