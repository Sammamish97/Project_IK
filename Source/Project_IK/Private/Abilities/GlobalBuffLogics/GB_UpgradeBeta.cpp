/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 07.14.2025
Summary : Source file for a global buff that upgrades hero Beta.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/GlobalBuffLogics/GB_UpgradeBeta.h"
#include "Characters/HeroBase.h"
#include "Components/CharacterStatComponent.h"

bool UGB_UpgradeBeta::IsBuffValidOnTarget(UObject* buff_target)
{
	AHeroBase* hero = Cast<AHeroBase>(buff_target);
	if (hero)
	{
		return hero->GetHeroType() == EHeroType::Hero2;
	}
	return false;
}

void UGB_UpgradeBeta::ApplyBuff(UObject* buff_target)
{
	if (AHeroBase* hero = Cast<AHeroBase>(buff_target))
	{
		
		hero->ApplyBuff(EBuffType::Upgrade_Beta, FBuffStatusData(ECharacterStatType::MagazineBonus, hero->GetCharacterStat()->GetAttackSpeed() * scaler_, false, true));

		// @@ TODO: Add buffUI after 
		// hero->AddBuffUI(FBuffUIData(FText::FromString("Upgrade Beta"), EBuffType::Upgrade_Beta, nullptr, 0.f, true, FText::FromString("Beta upgraded. Gain extra magazine bonus by its attack speed.")));
	}
}
