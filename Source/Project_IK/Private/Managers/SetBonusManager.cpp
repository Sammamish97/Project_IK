/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 3.9.2025
Summary : Source file for the Set Bonus Manager.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Managers/SetBonusManager.h"
#include "Abilities/SetBonuses/SetBonus_Chariot.h"

TObjectPtr<USetBonusBase> USetBonusManager::GetSetBonus(ERuneSetType type)
{
	switch (type)
	{
	case ERuneSetType::Chariot:
		return NewObject<USetBonus_Chariot>();
		break;
	}
	return nullptr;
}
