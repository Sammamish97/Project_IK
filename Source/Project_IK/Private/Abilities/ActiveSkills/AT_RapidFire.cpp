/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.15.2025
Summary : Source file for Rapid Fire Active Skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/ActiveSkills/AT_RapidFire.h"

#include "Characters/HeroBase.h"
#include "Components/CharacterStatComponent.h"
#include "Components/WeaponMechanics.h"
#include "Weapons/Guns/Gun.h"

UAT_RapidFire::UAT_RapidFire()
{
	target_param_ = FTargetParameters(ETargetingMode::Actor, ETargetType::Opponents, 1000.f);

	cool_time_ = 5.f;
}

bool UAT_RapidFire::ActivateSkill_Implementation(const FTargetResult& TargetResult)
{
	TWeakObjectPtr<AHeroBase> owner_hero_ptr = Cast<AHeroBase>(skill_owner_);
	if (auto hero = owner_hero_ptr.Get())
	{
		TWeakObjectPtr<AActor> target_ptr = TargetResult.target_actors_[0];
		if (auto target = target_ptr.Get())
		{
			hero->SetAttackTarget(target);

			auto weapon_mechanics_cache = hero->GetWeaponMechanics();
			auto weapon_actor = weapon_mechanics_cache->GetWeaponActor();

			weapon_mechanics_cache->StopFire();
			float total_fire_per_sec =  weapon_actor->GetWeaponData().fire_per_sec * (1 + hero->GetCharacterStat()->GetAttackSpeed() / 100.f);
			float weapon_attack_speed_double = 1.f / (total_fire_per_sec * attack_speed_increase_amount_);

			FTimerHandle& fire_timer_handle = weapon_mechanics_cache->RentFireTimerHandle();
			if(GetWorld()->GetTimerManager().IsTimerActive(fire_timer_handle) == false && target)
			{
				weapon_mechanics_cache->Reload();
				FTimerDelegate fire_del = FTimerDelegate::CreateUObject(this, &UAT_RapidFire::OnRapidFire, target, weapon_mechanics_cache, weapon_mechanics_cache->GetWeaponFireDamageData());
				GetWorld()->GetTimerManager().SetTimer(fire_timer_handle, fire_del, weapon_attack_speed_double, true, 0); 
			}
			return true;
		}
	}
	return false;
}

void UAT_RapidFire::OnRapidFire(AActor* target, class UWeaponMechanics* weapon_mechanics_cache, FDamageData dmg_data)
{
	weapon_mechanics_cache->OnFire(target, dmg_data);
	if (weapon_mechanics_cache->IsMagazineEmpty())
	{
		weapon_mechanics_cache->FinishFire();
	}
}
