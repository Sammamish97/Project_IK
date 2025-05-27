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
#include "Components/CharacterStatComponent.h"

void UWeaponMechanics::EquipWeapon(EWeaponType type)
{
	weapon_actor_ = GetWorld()->SpawnActor<AGunBase>(weapon_class_);
	weapon_actor_->AttachToComponent(owner_ref_->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, weapon_actor_->GetGrabSocketName());
	weapon_actor_->SetGunOwner(owner_ref_, owner_ref_->IsHero());
}

void UWeaponMechanics::BeginPlay()
{
	Super::BeginPlay();
	owner_ref_ = Cast<AUnit>(GetOwner());
}

void UWeaponMechanics::BeginFire(AActor* target)
{
	weapon_actor_->BeginFire(target);
}

void UWeaponMechanics::Reload(float duration_multiplier)
{
	weapon_actor_->Reload();
}

void UWeaponMechanics::FinishFire()
{
	weapon_actor_->FinishFire();
}

bool UWeaponMechanics::IsMagazineEmpty() const
{
	return weapon_actor_->IsMagazineEmpty();
}

FWeaponData UWeaponMechanics::GetWeaponData()
{
	if (weapon_actor_)
	{
		return weapon_actor_->GetWeaponData();
	}
	//TODO: 적절한 예외처리가 필요하다.
	return FWeaponData();
}

AGunBase* UWeaponMechanics::GetWeaponActor()
{
	return weapon_actor_;
}

FAIRequestID UWeaponMechanics::GetReloadRequestId() const
{
	if (weapon_actor_)
	{
		return weapon_actor_->GetReloadRequestId();
	}
	return -1;
}
