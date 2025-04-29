/******************************************************************************
Copyright(C) 2025
Author: Sinil Kang (rtd99062@gmail.com)
Creation Date : 4.28.2025
Summary : Source file for the Executioner passive skill.
					It gives attack speed for a second & reduce skill cooldown by a second.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/PassiveSkills/PS_Executioner.h"

#include "Subsystems/DelegateBridgeSubsystem.h"

void UPS_Executioner::InitEquipmentSkill(AActor* hero_ref)
{
	Super::InitEquipmentSkill(hero_ref);


	//hero_ref->GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnActiveSkill(this, &UPS_Agility::BuffAttackSpeed);
}
