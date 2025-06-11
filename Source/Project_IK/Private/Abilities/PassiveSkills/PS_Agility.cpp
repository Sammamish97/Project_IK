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
#include "Structs/BuffData.h"
#include "Characters/Unit.h"

void UPS_Agility::InitEquipmentSkill(AActor* hero_ref)
{
	Super::InitEquipmentSkill(hero_ref);
	//IKTODO: 바뀐 새로운 Decide - Delegate에 Bind해야 한다!
	//hero_ref->GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnActiveSkill(this, &UPS_Agility::BuffAttackSpeed);
}

void UPS_Agility::BuffAttackSpeed(EHeroType hero_idx)
{
	FBuffData attack_speed(TEXT("AgilityBuff"), ECharacterStatType::AttackSpeed, buff_amount_, is_buff_percentage_, buff_duration_);

	AActor* hero_actor = hero_cache_.Get();
	if (hero_actor)
	{
		AHeroBase* hero = Cast<AHeroBase>(hero_actor);
		if (hero->GetHeroType() == hero_idx)
		{
			hero->ApplyBuff(attack_speed);
		}
	}
}