/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 03.12.2025
Summary : Source file for a virtual super class that contains logic of a global buff.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/GlobalBuffLogics/GlobalBuffLogicBase.h"

bool UGlobalBuffLogicBase::IsBuffValidOnTarget(UObject* buff_target)
{
	return false;
}

void UGlobalBuffLogicBase::ApplyBuff(UObject* buff_target)
{
}

void UGlobalBuffLogicBase::OnBuffExpired()
{
}
