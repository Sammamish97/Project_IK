/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 07.21.2025
Summary : Source file for a global buff that applies shield to a hero when combat begins.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/GlobalBuffLogics/GB_AcquireShield.h"

#include "Characters/HeroBase.h"

bool UGB_AcquireShield::IsBuffValidOnTarget(UObject* buff_target)
{
	return buff_target->IsA<AHeroBase>();
}

void UGB_AcquireShield::ApplyBuff(UObject* buff_target)
{
	AHeroBase* hero = Cast<AHeroBase>(buff_target);
	if (hero)
	{
		hero->AcquireShield(shield_amount_, duration_);
	}
}
