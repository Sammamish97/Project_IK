/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.23.2025
Summary : Source file for magnetized bullet.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/Buffs/BF_MagnetizedBullet.h"

#include "Abilities/OnHitComponents/BulletMagnetizeEffectComponent.h"
#include "Characters/Unit.h"
#include "Components/WeaponMechanics.h"
#include "Weapons/Guns/GunBase.h"

void UBF_MagnetizedBullet::ApplyBuff(AUnit* target)
{
	Super::ApplyBuff(target);
	
	if (auto weapon_mechanics = target->GetComponentByClass<UWeaponMechanics>())
	{
		weapon_mechanics->GetWeaponActor()->AddOnHitComponent(magnetized_on_hit_class_);
	}
	FTimerDelegate timer_delegate = FTimerDelegate::CreateUObject(this, &UBF_MagnetizedBullet::RemoveBuff, target);
	GetWorld()->GetTimerManager().SetTimer(duration_timer_handle_, timer_delegate, duration_, false);
	target->AddBuffUI(buff_type_, display_data_, duration_);
}

void UBF_MagnetizedBullet::RemoveBuff(AUnit* target)
{
	if (auto weapon_mechanics = target->GetComponentByClass<UWeaponMechanics>())
	{
		weapon_mechanics->GetWeaponActor()->RemoveOnHitComponent(magnetized_on_hit_class_);
		GetWorld()->GetTimerManager().ClearTimer(duration_timer_handle_);
	}
	Super::RemoveBuff(target);
}

float UBF_MagnetizedBullet::GetDuration() const
{
	return duration_;
}
