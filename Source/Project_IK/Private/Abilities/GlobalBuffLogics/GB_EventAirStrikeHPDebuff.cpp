/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 07.22.2025
Summary : Source file for a global buff that decrease HP by the AirStrike event.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/GlobalBuffLogics/GB_EventAirStrikeHPDebuff.h"

#include "Characters/HeroBase.h"

bool UGB_EventAirStrikeHPDebuff::IsBuffValidOnTarget(UObject* buff_target)
{
	return buff_target->IsA<AHeroBase>();
}

void UGB_EventAirStrikeHPDebuff::ApplyBuff(UObject* buff_target)
{
	if (AHeroBase* hero = Cast<AHeroBase>(buff_target))
	{
		hero->ApplyBuff(EBuffType::AirStrikeHPDebuff, FBuffStatusData(ECharacterStatType::HitPoints, -0.3f, true, true));

		// @@ TODO: Add buffUI after 
		// hero->AddBuffUI(FBuffUIData(FText::FromString("AirStrike HP Debuff"), EBuffType::AirStrikeHPDebuff, nullptr, 0.f, true, FText::FromString("Wound by AirStrik not yet recovered, Max HP decreased by 30%.")));
	}
}
