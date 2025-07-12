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
#include "Weapons/Guns/GunBase.h"

#include "Kismet/KismetMathLibrary.h"
#include "Engine/SkeletalMeshSocket.h"

#include "Weapons/Skills/ShockJavelin.h"

UAT_ChargeShot::UAT_ChargeShot()
{
	target_param_ = FTargetParameters(ETargetingMode::Actor, ETargetType::Opponents, 1000.f);
	cool_time_ = 5.f;
}

bool UAT_ChargeShot::ActivateSkill(const FTargetResult& TargetResult)
{
	 AHeroBase* hero = Cast<AHeroBase>(skill_owner_);
	 if (hero)
	 {
	 	AActor* target = TargetResult.target_actors_[0];
	 	if (target)
	 	{
	 		auto weapon_mechanics_cache = hero->GetWeaponMechanics();
	 		

	 		weapon_mechanics_cache->FinishFire();
			// @@ TODO: This code is written under a couple of conditions
			// 1. FinishFire halts all AI actions.
			// 2. SetAttackTarget preserve data who is attack target after FinishFire is called.
			attack_target_ = target;
			GetWorld()->GetTimerManager().SetTimer(handler_, this, &UAT_ChargeShot::FireChargeShot, charge_time_);
	 		return true;
	 	}
	 }
	return Super::ActivateSkill(TargetResult);
}

void UAT_ChargeShot::FireChargeShot()
{
	AHeroBase* hero = Cast<AHeroBase>(skill_owner_);
	if (hero)
	{
		AActor* target = attack_target_.Get();
		if (target && charge_shot_class_)
		{
			// Fire ChargeShot

			AGunBase* weapon_actor = hero->GetWeaponMechanics()->GetWeaponActor();
			USkeletalMeshComponent* skeletal_mesh = weapon_actor->GetWeaponSkeletalMesh();
			const USkeletalMeshSocket* muzzle_socket = skeletal_mesh->GetSocketByName(weapon_actor->GetMuzzleSocketName());

			FTransform spawn_transform;
			if (muzzle_socket)
			{
				FVector muzzle_location = muzzle_socket->GetSocketLocation(skeletal_mesh) + FVector(50.f, 0.f, 50.f);
				FRotator rotation = UKismetMathLibrary::FindLookAtRotation(muzzle_location, target->GetActorLocation());
				spawn_transform.SetLocation(muzzle_location);
				spawn_transform.SetRotation(rotation.Quaternion());
			}
			else
			{
				spawn_transform.SetLocation(hero->GetActorLocation() + FVector(50.f, 0.f, 50.f));
				spawn_transform.SetRotation(hero->GetForwardDir().ToOrientationQuat());
			}

			AShockJavelin* spawned_javellin = GetWorld()->SpawnActor<AShockJavelin>(charge_shot_class_, spawn_transform);
			spawned_javellin->SetCastingTime(casting_time_);
			spawned_javellin->SetDamageData(FDamageData{ 0.f, weapon_actor->GetWeaponFireDamageData().atk_base_dmg_ * dmg_scale_, EDamageType::Magic, skill_owner_ });

			hero->GetWeaponMechanics()->BeginFire(target);
		}
		else
		{
			// When attack target has died,
			hero->GetWeaponMechanics()->BeginFire(nullptr);
		}
	}
	else
	{
		// When skill owner has died,
	}
}
