/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 03.12.2025
Summary : Source file for a global buff that remains bleeding on damaged targets.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/GlobalBuffLogics/WoundingBulletsBuffLogic.h"

#include "Subsystems/DelegateBridgeSubsystem.h"
#include "Characters/HeroBase.h"

bool UWoundingBulletsBuffLogic::IsBuffValidOnTarget(UObject* buff_target)
{
	return buff_target->IsA<AUnit>();
}

void UWoundingBulletsBuffLogic::ApplyBuff(UObject* buff_target)
{
	//GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnUnitDamageEvent(buff_target, EUnitEvent::OnHitBeforeCalc, this, &UWoundingBulletsBuffLogic::ApplyBleeding, FName(TEXT("UWoundingBulletsBuffLogic::ApplyBleeding")));
}

FDamageData UWoundingBulletsBuffLogic::ApplyBleeding(FDamageData data)
{
	TWeakObjectPtr<AUnit> unit = Cast<AUnit>(data.attack_target);
	unit->ApplyCrowdControl(ECCType::Bleeding, 5.f);
	return data;
}
