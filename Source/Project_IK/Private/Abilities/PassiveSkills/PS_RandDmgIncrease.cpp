/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.5.2025
Summary : Source file for the Random damage increase skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/PassiveSkills/PS_RandDmgIncrease.h"
#include "Subsystems/DelegateBridgeSubsystem.h"
void UPS_RandDmgIncrease::InitEquipmentSkill(AActor* hero_ref)
{
	Super::InitEquipmentSkill(hero_ref);
	//GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnUnitDamageEvent(hero_ref, EUnitEvent::OnFire, this, &UPS_RandDmgIncrease::OnEquipmentSkill);
}

FDamageData UPS_RandDmgIncrease::OnEquipmentSkill(FDamageData dmg_data)
{
	dmg_data.atk_base_dmg += FMath::RandRange(1, 5);
	return dmg_data;
}
