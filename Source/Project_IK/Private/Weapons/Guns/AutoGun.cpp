/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.27.2025
Summary : Source file for the Auto gun.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Weapons/Guns/AutoGun.h"

#include "Characters/HeroBase.h"
#include "Characters/Unit.h"
#include "Components/CharacterStatComponent.h"
#include "Components/WeaponMechanics.h"
#include "Kismet/KismetMathLibrary.h"

void AAutoGun::BeginFire(AActor* target)
{
	if (hold_action_)
	{
		return;
	}
	Super::BeginFire(target);
	TWeakObjectPtr<AActor> weak_target_ptr = target;
	if (AActor* target_ptr = weak_target_ptr.Get())
	{
		if(AUnit* gun_owner = weak_gun_owner_.Get())
		{
			float total_fire_per_sec =  weapon_status_data_.fire_per_sec * (1 + gun_owner->GetCharacterStat()->GetAttackSpeed() / 100.f);
			float weapon_attack_speed = 1.f / total_fire_per_sec;
			if(GetWorld()->GetTimerManager().IsTimerActive(fire_timer_handle_) == false && target_ptr)
			{
				OnFire(target_ptr, weapon_attack_speed);
			}
		}
	}
}

void AAutoGun::OnFire(AActor* target, float attack_speed)
{
	TWeakObjectPtr<AActor> weak_target_ptr = target;
	if (AActor* target_ptr = weak_target_ptr.Get())
	{
		if(AUnit* gun_owner = weak_gun_owner_.Get())
		{
			OnFireWeapon.Broadcast();
			gun_owner->PlayAnimMontage(fire_montage_, fire_montage_->GetPlayLength() / attack_speed);
			FVector rand_vec = UKismetMathLibrary::RandomUnitVector() * FMath::FRandRange(0.f, HARD_CODED_ACCURACY);
			if (weapon_status_data_.bullet_type == EBulletType::FMJ)
			{
				FireSingleBullet(target_ptr->GetActorLocation() + rand_vec, GetWeaponFireDamageData());
			}
			else if (weapon_status_data_.bullet_type == EBulletType::Buckshot)
			{
				FireBuckShot(target_ptr->GetActorLocation() + rand_vec, GetWeaponFireDamageData());
			}
		}
	}
	if (IsMagazineEmpty() == false)
	{
		if(AUnit* gun_owner = weak_gun_owner_.Get())
		{
			float total_fire_per_sec =  weapon_status_data_.fire_per_sec * (1 + gun_owner->GetCharacterStat()->GetAttackSpeed() / 100.f);
			float weapon_attack_speed = 1.f / total_fire_per_sec;
			FTimerDelegate fire_del = FTimerDelegate::CreateUObject(this, &AAutoGun::OnFire, gun_owner->GetAttackTarget(), weapon_attack_speed);
			GetWorld()->GetTimerManager().SetTimer(fire_timer_handle_, fire_del, weapon_attack_speed, false);
		}
	}
}