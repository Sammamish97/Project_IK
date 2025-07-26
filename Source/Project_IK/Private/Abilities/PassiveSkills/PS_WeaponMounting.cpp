/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.21.2025
Summary : Source file for the weapon mounting passive skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/PassiveSkills/PS_WeaponMounting.h"

#include "Subsystems/DelegateBridgeSubsystem.h"

void UPS_WeaponMounting::InitPassiveSkill(AActor* hero_ref, const FPassiveSkillData& skill_data)
{
	Super::InitPassiveSkill(hero_ref, skill_data);

	//hero_ref->GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnUnitEvent(hero_ref, EUnitEvent::HideOnCover, this, &UPS_WeaponMounting::ApplyBuff);
	//hero_ref->GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnUnitEvent(hero_ref, EUnitEvent::LeaveCover, this, &UPS_WeaponMounting::RemoveBuff);
	
	buff_status_data_ = FBuffStatusData(ECharacterStatType::AttackSpeed, 0.15f, true, true);
}

void UPS_WeaponMounting::ApplyBuff()
{
	if (is_buff_applied_ == false)
	{
		if (AActor* actor = hero_cache_.Get())
		{
			if (AHeroBase* hero = Cast<AHeroBase>(actor))
			{
				hero->ApplyStatusBuff(EBuffType::WeaponMounting, buff_status_data_);
				//hero->AddBuffUI(FBuffUIData(skill_data_.item_data_, EBuffType::WeaponMounting, buff_status_data_.duration_, true));

				is_buff_applied_ = true;
			}
		}
	}
}

void UPS_WeaponMounting::RemoveBuff()
{
	if (is_buff_applied_)
	{
		if (AActor* actor = hero_cache_.Get())
		{
			if (AHeroBase* unit = Cast<AHeroBase>(actor))
			{
				unit->RemoveBuff(EBuffType::WeaponMounting);
				unit->RemoveBuffUI(EBuffType::WeaponMounting);
				is_buff_applied_ = false;
			}
		}
	}
}
