/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 07.14.2025
Summary : Source file for a global buff that upgrades hero Omega.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/GlobalBuffLogics/GB_UpgradeOmega.h"
#include "Characters/HeroBase.h"
#include "Components/CharacterStatComponent.h"

bool UGB_UpgradeOmega::IsBuffValidOnTarget(UObject* buff_target)
{
	AHeroBase* hero = Cast<AHeroBase>(buff_target);
	if (hero)
	{
		return hero->GetHeroType() == EHeroType::Hero3;
	}
	return false;
}

void UGB_UpgradeOmega::ApplyBuff(UObject* buff_target)
{
	if (AHeroBase* hero = Cast<AHeroBase>(buff_target))
	{

		float max_hp = hero->GetCharacterStat()->GetMaxHitPoint();
		hero->ApplyStatusBuff(EBuffType::Upgrade_Gamma, FBuffStatusData(ECharacterStatType::AttackPower, max_hp * attack_power_scaler_, false, true));
		hero->ApplyStatusBuff(EBuffType::Upgrade_Gamma, FBuffStatusData(ECharacterStatType::SkillPower, max_hp * skill_power_scaler_, false, true));

		// @@ TODO: Add buffUI after 
		// hero->AddBuffUI(FBuffUIData(FText::FromString("Upgrade Omega"), EBuffType::Upgrade_Omega, nullptr, 0.f, true, FText::FromString("Omega upgraded. Gain extra attack power & skill power bonus by its max hit points.")));
	}
}
