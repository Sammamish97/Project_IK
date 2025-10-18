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
#include "Components/CharacterStatComponent.h"
#include "Weapons/Guns/GunBase.h"

#include "Kismet/KismetMathLibrary.h"
#include "Engine/SkeletalMeshSocket.h"

#include "Weapons/Skills/ChargeShot.h"

UAT_ChargeShot::UAT_ChargeShot()
{
	target_param_ = FTargetParameters(ETargetingMode::Actor, ETargetType::Opponents, 1000.f);
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
	 		

			// 1. FinishFire halts all AI actions.
	 		weapon_mechanics_cache->FinishFire();
			FireChargeShot(target);
			GetWorld()->GetTimerManager().SetTimer(handler_, this, &UAT_ChargeShot::ResumeFiring, charge_time_);
			return Super::ActivateSkill(TargetResult);
	 	}
	 }
	 return false;
}

void UAT_ChargeShot::ResumeFiring()
{
	// Resume AI behavior

	if (chargeshot_)
	{ 
		if (!IsValid(skill_owner_)) 
		{
			// When skill owner (hero) has died,
			chargeshot_->Destroy();
		}
	}
}

void UAT_ChargeShot::FireChargeShot(AActor* target)
{
	AHeroBase* hero = Cast<AHeroBase>(skill_owner_);
	if (hero)
	{
		if (charge_shot_class_)
		{
			// Fire ChargeShot

			AGunBase* weapon_actor = hero->GetWeaponMechanics()->GetWeaponActor();
			USkeletalMeshComponent* skeletal_mesh = weapon_actor->GetWeaponSkeletalMesh();
			const USkeletalMeshSocket* muzzle_socket = skeletal_mesh->GetSocketByName(weapon_actor->GetMuzzleSocketName());

			FTransform spawn_transform;
			if (muzzle_socket)
			{
				FVector muzzle_location = muzzle_socket->GetSocketLocation(skeletal_mesh);
				spawn_transform.SetLocation(muzzle_location);
			}
			else
			{
				spawn_transform.SetLocation(weapon_actor->GetActorLocation() + FVector(50.f, 0.f, 0.f));
			}
			FRotator rotation = UKismetMathLibrary::FindLookAtRotation(spawn_transform.GetLocation(), target->GetActorLocation());
			spawn_transform.SetRotation(rotation.Quaternion());

			chargeshot_ = GetWorld()->SpawnActor<AChargeShot>(charge_shot_class_, spawn_transform);
			if (chargeshot_)
			{
				float skill_power_scale = 1.f;
				if (skill_data_.skill_power_scales_.IsEmpty() == false)
				{
					skill_data_.skill_power_scales_[0];
				}
				chargeshot_->SetCastingTime(charge_time_);
				chargeshot_->SetDamageData(FDamageData{ 0.f, weapon_actor->GetWeaponFireDamageData().atk_base_dmg_ * dmg_scale_ + (hero->GetCharacterStat()->GetSkillPower() * skill_power_scale), EDamageType::Magic, skill_owner_ });
			}

			hero->GetWeaponMechanics()->BeginFire(target);
		}
	}
}
