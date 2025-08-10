/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.28.2025
Summary : Source file for the Rund Adn Gun Buff.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/Buffs/BF_RunAndGun.h"

#include "Characters/Unit.h"
#include "Subsystems/DelegateBridgeSubsystem.h"

class UDelegateBridgeSubsystem;

void UBF_RunAndGun::ApplyBuff(AUnit* target)
{
	Super::ApplyBuff(target);
	target_cache_ = target;
	GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnUnitEvent(target_cache_.Get(), EUnitEvent::OnReposition, this, &UBF_RunAndGun::OnReposition);
	target->AddBuffUI(EBuffType::RunAndGun, display_data_);
}

void UBF_RunAndGun::OnReposition()
{
	if (auto target_ptr = target_cache_.Get())
	{
		Cast<AHeroBase>(target_ptr)->GetWeaponMechanics()->InstantReload();
	}
}
