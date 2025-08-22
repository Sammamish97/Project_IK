/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 07.26.2025
Summary : Source file for a global buff that apply buff using BF_OneStatusBuff.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/GlobalBuffLogics/GB_ApplyBuffToActor.h"

#include "Characters/Unit.h"
#include "Abilities/Buffs/BuffHandler.h"

bool UGB_ApplyBuffToActor::IsBuffValidOnTarget(UObject* buff_target)
{
	return buff_target->IsA(buff_target_class_);
}

void UGB_ApplyBuffToActor::ApplyBuff(UObject* buff_target)
{
	UBuffHandler* handler = NewObject<UBuffHandler>(this, buff_class_);
	handler->ApplyBuff(Cast<AUnit>(buff_target));
}
