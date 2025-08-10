/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.03.2024
Summary : Source file for WeaponMechanics.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Components/WeaponMechanics.h"
#include "Weapons/Guns/GunBase.h"
#include "Characters/Unit.h"

void UWeaponMechanics::EquipWeapon(TSubclassOf<AGunBase> weapon_class)
{
	weapon_actor_ = GetWorld()->SpawnActor<AGunBase>(weapon_class);
	weapon_actor_->AttachToComponent(owner_ref_->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, weapon_actor_->GetGrabSocketName());
	weapon_actor_->SetGunOwner(owner_ref_, owner_ref_->IsHero());
}

void UWeaponMechanics::BeginPlay()
{
	Super::BeginPlay();
	owner_ref_ = Cast<AUnit>(GetOwner());
}

void UWeaponMechanics::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	weapon_actor_->Destroy();
}

void UWeaponMechanics::BeginFire(AActor* target)
{
	weapon_actor_->BeginFire(target);
}

void UWeaponMechanics::InstantReload()
{
	weapon_actor_->InstantReload();
}

void UWeaponMechanics::Reload()
{
	weapon_actor_->Reload();
}

void UWeaponMechanics::StopReload()
{
	weapon_actor_->StopReload();
}

void UWeaponMechanics::FinishFire()
{
	weapon_actor_->FinishFire();
}

bool UWeaponMechanics::IsMagazineEmpty() const
{
	return weapon_actor_->IsMagazineEmpty();
}

FWeaponStatusData UWeaponMechanics::GetWeaponData()
{
	if (weapon_actor_)
	{
		return weapon_actor_->GetWeaponStatusData();
	}
	//TODO: 적절한 예외처리가 필요하다.
	return FWeaponStatusData();
}

void UWeaponMechanics::SetHoldAction(bool hold_action)
{
	weapon_actor_->SetHoldAction(hold_action);
}

AGunBase* UWeaponMechanics::GetWeaponActor()
{
	return weapon_actor_;
}

void UWeaponMechanics::DieWeaponActor()
{
	weapon_actor_->Die();
}
