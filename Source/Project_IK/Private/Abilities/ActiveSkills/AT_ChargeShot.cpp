/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.12.2025
Summary : Source file for Charge Shot Active Skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/ActiveSkills/AT_ChargeShot.h"
#include "Characters/HeroBase.h"
#include "Components/WeaponMechanics.h"
#include "Weapons/Guns/Gun.h"

UAT_ChargeShot::UAT_ChargeShot()
{
	target_param_ = FTargetParameters(ETargetingMode::Actor, ETargetType::Opponents, 1000.f);
	cool_time_ = 5.f;
}

bool UAT_ChargeShot::ActivateSkill_Implementation(const FTargetResult& TargetResult)
{
	TWeakObjectPtr<AHeroBase> owner_hero_ptr = Cast<AHeroBase>(skill_owner_);
	if (owner_hero_ptr.IsValid())
	{
		AHeroBase* hero = owner_hero_ptr.Get();
		TWeakObjectPtr<AActor> target_ptr = TargetResult.target_actors_[0];
		if (target_ptr.IsValid())
		{
			AActor* target = target_ptr.Get();
			hero->SetAttackTarget(target);
			auto weapon_mechanics_cache = hero->GetWeaponMechanics();
			
			weapon_mechanics_cache->StopFire();
			FTimerHandle& fire_timer_handle = weapon_mechanics_cache->RentFireTimerHandle();

			if(GetWorld()->GetTimerManager().IsTimerActive(fire_timer_handle) == false && target)
			{
				weapon_mechanics_cache->GetWeaponActor()->Reload(1);
				FDamageData dmg_data = weapon_mechanics_cache->GetWeaponFireDamageData();
				dmg_data.atk_base_dmg *= dmg_scale_;
				FTimerDelegate fire_del = FTimerDelegate::CreateUObject(this, &UAT_ChargeShot::OnChargeShot, target, weapon_mechanics_cache, dmg_data);
				GetWorld()->GetTimerManager().SetTimer(fire_timer_handle, fire_del, charge_time_, false, charge_time_); 
			}
			return true;
		}
	}
	return false;
}

void UAT_ChargeShot::OnChargeShot(AActor* target, UWeaponMechanics* weapon_mechanics_cache, FDamageData dmg_data)
{
	weapon_mechanics_cache->OnFire(target, dmg_data);
	weapon_mechanics_cache->FinishFire();
	weapon_mechanics_cache->ResumeFire();
}