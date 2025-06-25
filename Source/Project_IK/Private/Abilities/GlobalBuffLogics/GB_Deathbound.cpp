/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 03.12.2025
Summary : Header file for a global buff that applies to a hero that has been dead.

Licensed under the MIT Lice	nse.
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
}
