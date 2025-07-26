/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 03.12.2025
Summary : Source file for a global buff that applies to a hero that has been dead.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/GlobalBuffLogics/GB_Deathbound.h"

#include "Managers/EnumCluster.h"
#include "Characters/HeroBase.h"

bool UGB_Deathbound::IsBuffValidOnTarget(UObject* buff_target)
{
	AHeroBase* hero = Cast<AHeroBase>(buff_target);
	if (hero)
	{
		return hero->GetHeroType() == target_hero_type_;
	}
	return false;
}

void UGB_Deathbound::ApplyBuff(UObject* buff_target)
{
	if (AHeroBase* hero = Cast<AHeroBase>(buff_target))
	{
		hero->ApplyStatusBuff(EBuffType::Deathbound, FBuffStatusData(ECharacterStatType::HitPoints, 0.5f, true, true));
		hero->ApplyStatusBuff(EBuffType::Deathbound, FBuffStatusData(ECharacterStatType::AttackPower, 0.5f, true, true));
		hero->ApplyStatusBuff(EBuffType::Deathbound, FBuffStatusData(ECharacterStatType::AttackSpeed, 0.5f, true, true));

		//IKTODO: DeathBound를 위한 FBuffData가 필요함.
		//hero->AddBuffUI(FBuffUIData(FText::FromString("Deathbound"), EBuffType::Deathbound, nullptr, 0.f, true, FText::FromString("x0.5 HP, AttackPower, AttackSpeed")));
	}
}
