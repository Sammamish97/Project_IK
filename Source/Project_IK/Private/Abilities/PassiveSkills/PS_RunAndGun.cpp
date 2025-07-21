/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.21.2025
Summary : Source file for the run and gun passive skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/PassiveSkills/PS_RunAndGun.h"

#include "Subsystems/DelegateBridgeSubsystem.h"

void UPS_RunAndGun::InitPassiveSkill(AActor* hero_ref, const FPassiveSkillData& skill_data)
{
	Super::InitPassiveSkill(hero_ref, skill_data);
	hero_ref->GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnUnitEvent(hero_ref, EUnitEvent::OnReposition, this, &UPS_RunAndGun::OnReposition);
}

void UPS_RunAndGun::OnReposition()
{
	Cast<AHeroBase>(hero_cache_)->GetWeaponMechanics()->InstantReload();
}
