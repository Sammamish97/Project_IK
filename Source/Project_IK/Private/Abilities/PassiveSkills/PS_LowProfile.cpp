/******************************************************************************
Copyright(C) 2025
Author: Sinil Kang (rtd99062@gmail.com)
Creation Date : 5.2.2025
Summary : Source file for the low profile passive skill.
					It gives evasion rate buffs when they are not in cover.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/PassiveSkills/PS_LowProfile.h"

#include "Subsystems/DelegateBridgeSubsystem.h"

void UPS_LowProfile::InitEquipmentSkill(AActor* hero_ref)
{
	Super::InitEquipmentSkill(hero_ref);

	hero_ref->GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnUnitEvent(hero_ref, EUnitEvent::HideOnCover, this, &UPS_LowProfile::RemoveBuff);
	hero_ref->GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnUnitEvent(hero_ref, EUnitEvent::LeaveCover, this, &UPS_LowProfile::ApplyBuff);

	ApplyBuff();
}

void UPS_LowProfile::ApplyBuff()
{
	if (is_buff_applied_ == false)
	{
		AActor* actor = hero_cache_.Get();
		if (actor)
		{
			AUnit* unit = Cast<AUnit>(actor);
			if (unit)
			{
				FBuffData evade_rate(TEXT("LowProfile"), ECharacterStatType::EvasionRate, evasion_rate_buff_amount_, is_evasion_rate_buff_percentage_, true);
				unit->ApplyBuff(evade_rate);

				is_buff_applied_ = true;
			}
		}
	}
}

void UPS_LowProfile::RemoveBuff()
{
	if (is_buff_applied_)
	{
		AActor* actor = hero_cache_.Get();
		if (actor)
		{
			AUnit* unit = Cast<AUnit>(actor);
			if (unit)
			{
				unit->RemoveBuff(TEXT("LowProfile"));


				is_buff_applied_ = false;
			}
		}
	}
}