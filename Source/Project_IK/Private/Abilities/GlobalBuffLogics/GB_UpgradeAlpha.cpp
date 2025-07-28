/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 07.14.2025
Summary : Source file for a global buff that upgrades hero Alpha.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/GlobalBuffLogics/GB_UpgradeAlpha.h"

#include "Characters/HeroBase.h"
#include "Structs/BuffStatusData.h"

bool UGB_UpgradeAlpha::IsBuffValidOnTarget(UObject* buff_target)
{
	AHeroBase* hero = Cast<AHeroBase>(buff_target);
	if (hero)
	{
		return hero->GetHeroType() == EHeroType::Hero1;
	}
	return false;
}

void UGB_UpgradeAlpha::ApplyBuff(UObject* buff_target)
{
	if (AHeroBase* hero = Cast<AHeroBase>(buff_target))
	{
		hero->ApplyStatusBuff(EBuffType::Upgrade_Alpha, FBuffStatusData(ECharacterStatType::AttackPower, 0.3f, true, true));

		// @@ TODO: Add buffUI after 
		// hero->AddBuffUI(FBuffUIData(FText::FromString("Upgrade Alpha"), EBuffType::Upgrade_Alpha, nullptr, 0.f, true, FText::FromString("Alpha upgraded. Gets 30% extra attack&magic power")));
	}

}
