/******************************************************************************
Copyright(C) 2025
Author: Sinil Kang (rtd99062@gmail.com)
Creation Date : 4.25.2025
Summary : Source file for the agility skill.
					It buffs attack speed rate after active skill is invoked.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/PassiveSkills/PS_Agility.h"

#include "Subsystems/DelegateBridgeSubsystem.h"
#include "Characters/Unit.h"
#include "DataAssets/BuffDataAsset.h"

void UPS_Agility::InitEquipmentSkill(AActor* hero_ref)
{
	Super::InitEquipmentSkill(hero_ref);
	hero_ref->GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnUnitEvent(hero_ref, EUnitEvent::OnActiveSkill, this, &UPS_Agility::BuffAttackSpeed);
}

void UPS_Agility::BuffAttackSpeed()
{
	 if (AActor* hero_actor = hero_cache_.Get())
	 {
	 	if(AUnit* hero = Cast<AUnit>(hero_actor))
	 	{
	 		//hero->ApplyBuff(buff_data_asset_->buff_data_);
	 	}
	 }
}
