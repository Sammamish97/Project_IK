/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 07.14.2025
Summary : Source file for a global buff that upgrades hero Gamma.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/GlobalBuffLogics/GB_UpgradeGamma.h"
#include "Characters/HeroBase.h"

bool UGB_UpgradeGamma::IsBuffValidOnTarget(UObject* buff_target)
{
	AHeroBase* hero = Cast<AHeroBase>(buff_target);
	if (hero)
	{
		return hero->GetHeroType() == EHeroType::Hero3;
	}
	return false;
}

void UGB_UpgradeGamma::ApplyBuff(UObject* buff_target)
{
	if (AHeroBase* hero = Cast<AHeroBase>(buff_target))
	{

		hero->ApplyStatusBuff(EBuffType::Upgrade_Gamma, FBuffStatusData(ECharacterStatType::SkillPower, 10.f, false, true));

		// @@ TODO: Add buffUI after 
		// hero->AddBuffUI(FBuffUIData(FText::FromString("Upgrade Gamma"), EBuffType::Upgrade_Gamma, nullptr, 0.f, true, FText::FromString("Gamma upgraded. Gain 10 skill power.")));
	}
}
