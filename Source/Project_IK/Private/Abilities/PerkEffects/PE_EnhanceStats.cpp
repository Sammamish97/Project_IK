/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 7.13.2025
Summary : Source file for perk effects that enhance hero stat data.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/PerkEffects/PE_EnhanceStats.h"

#include "WorldSettings/IKGameInstance.h"

void UPE_EnhanceStats::ApplyEffect()
{
	UWorld* world = GetWorld();
	if (world)
	{
		UIKGameInstance* instance = Cast<UIKGameInstance>(world->GetGameInstance());
		if (instance)
		{
			instance->EnhanceHeroesStatData(stat_, modifier_);
		}
	}
}

void UPE_EnhanceStats::RemoveEffect()
{
	UWorld* world = GetWorld();
	if (world)
	{
		UIKGameInstance* instance = Cast<UIKGameInstance>(world->GetGameInstance());
		if (instance)
		{
			instance->DiminishHeroesStatData(stat_, modifier_);
		}
	}
}
