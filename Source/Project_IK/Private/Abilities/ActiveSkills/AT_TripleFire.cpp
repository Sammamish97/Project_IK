/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.12.2025
Summary : Source file for TripleFire Active Skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Abilities/ActiveSkills/AT_TripleFire.h"

#include "Characters/HeroBase.h"
#include "Components/CharacterStatComponent.h"
#include "Components/WeaponMechanics.h"
#include "Weapons/Guns/GunBase.h"

UAT_TripleFire::UAT_TripleFire()
{
	target_param_ = FTargetParameters(ETargetingMode::Actor, ETargetType::Opponents, 1000.f);

	cool_time_ = 5.f;
}

TOptional<FTargetParameters> UAT_TripleFire::ActivateSkill(const FTargetResult& TargetResult)
{
	// TWeakObjectPtr<AHeroBase> owner_hero_ptr = Cast<AHeroBase>(skill_owner_);
	// if (auto hero = owner_hero_ptr.Get())
	// {
	// 	TWeakObjectPtr<AActor> target_ptr = TargetResult.target_actors_[0];
	// 	if (auto target = target_ptr.Get())
	// 	{
	// 		hero->SetAttackTarget(target);
	//
	// 		auto weapon_mechanics_cache = hero->GetWeaponMechanics();
	// 		auto weapon_actor = weapon_mechanics_cache->GetWeaponActor();
	//
	// 		weapon_mechanics_cache->StopFire();
	// 		float total_fire_per_sec =  weapon_actor->GetWeaponData().fire_per_sec * (1 + hero->GetCharacterStat()->GetAttackSpeed() / 100.f);
	// 		float boosted_attack_speed = 1.f / (total_fire_per_sec * attack_speed_increase_amount_);
	//
	// 		FTimerHandle& fire_timer_handle = weapon_mechanics_cache->RentFireTimerHandle();
	// 		if(GetWorld()->GetTimerManager().IsTimerActive(fire_timer_handle) == false && target)
	// 		{
	// 			weapon_actor->Reload(3);
	// 			
	// 			FTimerDelegate fire_del = FTimerDelegate::CreateUObject(this, &UAT_TripleFire::OnTripleFire, target, weapon_mechanics_cache, weapon_mechanics_cache->GetWeaponFireDamageData(), boosted_attack_speed);
	// 			GetWorld()->GetTimerManager().SetTimer(fire_timer_handle, fire_del, boosted_attack_speed, true, 0); 
	// 		}
	// 		return true;
	// 	}
	// }
	return NullOpt;
}

void UAT_TripleFire::OnTripleFire(AActor* target, UWeaponMechanics* weapon_mechanics_cache, FDamageData dmg_data, float attack_speed)
{
	// static int32 counter = 0;
	// counter += 1;
	// weapon_mechanics_cache->OnFire(target, dmg_data, attack_speed);
	// if (counter == 3)
	// {
	// 	counter = 0;
	// 	weapon_mechanics_cache->FinishFire();
	// 	weapon_mechanics_cache->ResumeFire();
	// }
}