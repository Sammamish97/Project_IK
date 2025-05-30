/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 3.9.2025
Summary : Source file for the Set Bonus Base.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/SetBonuses/SetBonusBase.h"

void USetBonusBase::ActivateSetBonus(TObjectPtr<AHeroBase> owner, int32 set_amount)
{
	hero_cache_ = owner;
	if (set_amount == 2)
	{
		ActivateEdgeBonus();
	}
	else if (set_amount == 3)
	{
		ActivateTriangleBonus();
	}
	else if (set_amount == 6)
	{
		ActivateHexagonBonus();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Wrong node amount for the Set Bonus!"));
	}
}

void USetBonusBase::ActivateEdgeBonus()
{
}

void USetBonusBase::ActivateTriangleBonus()
{
	ActivateEdgeBonus();
}

void USetBonusBase::ActivateHexagonBonus()
{
	ActivateTriangleBonus();
}
