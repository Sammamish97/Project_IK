/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 07.23.2025
Summary : Source file for a global buff that decrease AttackSpeed by the Ambush event.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/GlobalBuffLogics/GB_EventAmbushAttackSpeedDebuff.h"

#include "Characters/HeroBase.h"

bool UGB_EventAmbushAttackSpeedDebuff::IsBuffValidOnTarget(UObject* buff_target)
{
	return buff_target->IsA<AHeroBase>();
}

void UGB_EventAmbushAttackSpeedDebuff::ApplyBuff(UObject* buff_target)
{
	if (AHeroBase* hero = Cast<AHeroBase>(buff_target))
	{
		hero->ApplyBuff(EBuffType::AmbushAttackSpeedDebuff, FBuffStatusData(ECharacterStatType::AttackSpeed, -0.15f, true, true));

		// @@ TODO: Add buffUI after 
		// hero->AddBuffUI(FBuffUIData(FText::FromString("Ambush AttackSpeed Debuff"), EBuffType::AmbushAttackSpeedDebuff, nullptr, 0.f, true, FText::FromString("Ambushed! AttackSpeed decreased by 15%.")));
	}
}
