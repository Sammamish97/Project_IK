/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.27.2025
Summary : Source file for the Burst Gun.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Weapons/Guns/BurstGun.h"

#include "Characters/Unit.h"
#include "Components/CharacterStatComponent.h"
#include "Kismet/KismetMathLibrary.h"

void ABurstGun::BeginFire(AActor* target)
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
			if (on_burst_cool_down_ == false)
			{
				if(GetWorld()->GetTimerManager().IsTimerActive(fire_timer_handle_) == false && target_ptr)
				{
					FTimerDelegate fire_del = FTimerDelegate::CreateUObject(this, &ABurstGun::OnFire, target_ptr, GetWeaponFireDamageData(), weapon_attack_speed);
					GetWorld()->GetTimerManager().SetTimer(fire_timer_handle_, fire_del, weapon_attack_speed, true, weapon_attack_speed); 
				}
			}
		}
	}
}

void ABurstGun::OnFire(AActor* target, FDamageData dmg_data, float attack_speed)
{
	TWeakObjectPtr<AActor> weak_target_ptr = target;
	if (AActor* target_ptr = weak_target_ptr.Get())
	{
		if(AUnit* gun_owner = weak_gun_owner_.Get())
		{
			burst_count_ += 1;
			gun_owner->PlayAnimMontage(fire_montage_, fire_montage_->GetPlayLength() / attack_speed);
			FVector rand_vec = UKismetMathLibrary::RandomUnitVector() * FMath::FRandRange(0.f, HARD_CODED_ACCURACY);
			FireSingleBullet(target_ptr->GetActorLocation() + rand_vec, GetWeaponFireDamageData());
			
			if (burst_count_ >= burst_amount_)
			{
				on_burst_cool_down_ = true;
				FinishFire();
				FTimerDelegate burst_del = FTimerDelegate::CreateUObject(this, &ABurstGun::FinishBurstCooldown);
				float burst_wait_time = wait_after_burst_ / (1 + gun_owner->GetCharacterStat()->GetAttackSpeed() / 100.f);
				GetWorld()->GetTimerManager().SetTimer(burst_timer_handle_, burst_del, burst_wait_time, false); 
			}
		}
	}
	if(IsMagazineEmpty())
	{
		FinishFire();
	}
}

void ABurstGun::OnReload()
{
	Super::OnReload();
	burst_count_ = 0;
}

void ABurstGun::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearTimer(burst_timer_handle_);
	Super::EndPlay(EndPlayReason);
}

void ABurstGun::FinishBurstCooldown()
{
	GetWorld()->GetTimerManager().ClearTimer(burst_timer_handle_);
	burst_count_ = 0;
	on_burst_cool_down_ = false;
}
