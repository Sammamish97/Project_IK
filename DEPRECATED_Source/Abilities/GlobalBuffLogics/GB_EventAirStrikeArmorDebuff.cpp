/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 07.22.2025
Summary : Source file for a global buff that decrease Armor by the AirStrike event.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/GlobalBuffLogics/GB_EventAirStrikeArmorDebuff.h"

#include "Characters/HeroBase.h"

bool UGB_EventAirStrikeArmorDebuff::IsBuffValidOnTarget(UObject* buff_target)
{
	return buff_target->IsA<AHeroBase>();
}

void UGB_EventAirStrikeArmorDebuff::ApplyBuff(UObject* buff_target)
{
	if (AHeroBase* hero = Cast<AHeroBase>(buff_target))
	{
		// hero->ApplyBuff(EBuffType::AirStrikeArmorDebuff, FBuffStatusData(ECharacterStatType::Armor, -0.2f, true, true));

		// @@ TODO: Add buffUI after 
		// hero->AddBuffUI(FBuffUIData(FText::FromString("AirStrike Armor Debuff"), EBuffType::AirStrikeArmorDebuff, nullptr, 0.f, true, FText::FromString("Armor crashed, armor efficient decreased by 20%.")));
	}
}
