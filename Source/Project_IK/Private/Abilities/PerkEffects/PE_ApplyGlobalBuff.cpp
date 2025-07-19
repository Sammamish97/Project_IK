/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 7.14.2025
Summary : Source file for perk effects that apply GlobalBuff.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/PerkEffects/PE_ApplyGlobalBuff.h"
#include "Subsystems/GlobalBuffSubsystem.h"

void UPE_ApplyGlobalBuff::ApplyEffect()
{
	UGlobalBuffSubsystem* global_buff_subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UGlobalBuffSubsystem>();
	if (global_buff_subsystem)
	{
		global_buff_subsystem->AddEverlastingBuff(global_buff_type_);
	}
}

void UPE_ApplyGlobalBuff::RemoveEffect()
{
	UGlobalBuffSubsystem* global_buff_subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UGlobalBuffSubsystem>();
	if (global_buff_subsystem)
	{
		global_buff_subsystem->RemoveEverlastingBuff(global_buff_type_);
	}
}
