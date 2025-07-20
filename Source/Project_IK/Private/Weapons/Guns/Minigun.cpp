/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.27.2025
Summary : Source file for the minigun.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Weapons/Guns/Minigun.h"

#include "Animations/MinigunAnimInstance.h"
#include "Characters/Unit.h"
#include "Components/CharacterStatComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Weapons/Guns/AutoGun.h"

void AMinigun::BeginFire(AActor* target)
{
	if (hold_action_)
	{
		return;
	}
	Super::BeginFire(target);
	if(GetWorld()->GetTimerManager().IsTimerActive(pre_heat_timer_) == false && on_fire_ == false)
	{
		on_fire_ = true;
		FTimerDelegate fire_del = FTimerDelegate::CreateUObject(this, &AMinigun::OnFinishPreheat, target);
		GetWorld()->GetTimerManager().SetTimer(pre_heat_timer_, fire_del, pre_heat_time_, false);
		//예열 Anim Play
		Cast<UMinigunAnimInstance>(GetWeaponSkeletalMesh()->GetAnimInstance())->SetMinigunState(EMinigunAnimState::PreHeating);
	}
}

void AMinigun::OnFinishPreheat(AActor* target)
{
	TWeakObjectPtr<AActor> weak_target_ptr = target;
	if (AActor* target_ptr = weak_target_ptr.Get())
	{
		if(AUnit* gun_owner = weak_gun_owner_.Get())
		{
			//발사 Anim Play
			Cast<UMinigunAnimInstance>(GetWeaponSkeletalMesh()->GetAnimInstance())->SetMinigunState(EMinigunAnimState::OnFire);

			float total_fire_per_sec =  weapon_status_data_.fire_per_sec * (1 + gun_owner->GetCharacterStat()->GetAttackSpeed() / 100.f);
			float weapon_attack_speed = 1.f / total_fire_per_sec;
			if(GetWorld()->GetTimerManager().IsTimerActive(fire_timer_handle_) == false && target_ptr)
			{
				FTimerDelegate fire_del = FTimerDelegate::CreateUObject(this, &AMinigun::OnFire, target_ptr);
				GetWorld()->GetTimerManager().SetTimer(fire_timer_handle_, fire_del, weapon_attack_speed, true, pre_heat_time_);
			}
		}
	}
}

void AMinigun::OnFire(AActor* target)
{
	TWeakObjectPtr<AActor> weak_target_ptr = target;
	if (AActor* target_ptr = weak_target_ptr.Get())
	{
		FVector rand_vec = UKismetMathLibrary::RandomUnitVector() * FMath::FRandRange(0.f, HARD_CODED_ACCURACY);
		FireSingleBullet(target_ptr->GetActorLocation() + rand_vec, GetWeaponFireDamageData());
	}
	if(IsMagazineEmpty())
	{
		FinishFire();
	}
}

void AMinigun::FinishFire()
{
	Super::FinishFire();
	Cast<UMinigunAnimInstance>(GetWeaponSkeletalMesh()->GetAnimInstance())->SetMinigunState(EMinigunAnimState::Cooling);
	on_fire_ = false;
}
