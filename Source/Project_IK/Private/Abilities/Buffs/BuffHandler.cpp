/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.22.2025
Summary : Source file for Buff Base.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/Buffs/BuffHandler.h"
#include "Characters/Unit.h"
void UBuffHandler::ApplyBuff(AUnit* target)
{
	target_cache_ = target;
}

void UBuffHandler::RemoveBuff(AUnit* target)
{
	target_cache_ = nullptr;
}