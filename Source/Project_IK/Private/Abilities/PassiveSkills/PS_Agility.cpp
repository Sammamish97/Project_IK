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

	duration_ = 3.f;
	as_buff_amount_ = 2.0f;
	buff_status_data_ = FBuffStatusData(ECharacterStatType::AttackSpeed, as_buff_amount_, true, false, duration_);
	buff_ui_data_ = FBuffUIData(FText::FromString("Agility"), EBuffType::Agility, nullptr, duration_, false, FText::FromString("Agility Detail"));
}

void UPS_Agility::BuffAttackSpeed()
{
	 if (AActor* hero_actor = hero_cache_.Get())
	 {
	 	if(AHeroBase* hero = Cast<AHeroBase>(hero_actor))
	 	{
	 		hero->ApplyBuff(EBuffType::Agility, buff_status_data_);
	 		hero->AddBuffUI(buff_ui_data_);
	 	}
	 }
}
