/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.08.2024
Summary : Source file for Passive Gunner Enemy.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Characters/PassiveGunnerEnemy.h"
#include "Components/CharacterStatComponent.h"
#include "Components/WeaponMechanics.h"

APassiveGunnerEnemy::APassiveGunnerEnemy()
{
	weapon_mechanics_ = CreateDefaultSubobject<UWeaponMechanics>(TEXT("WeaponMechanics"));
}

void APassiveGunnerEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void APassiveGunnerEnemy::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void APassiveGunnerEnemy::Die()
{
	weapon_mechanics_->OnDestroy();
	Super::Die();
}

void APassiveGunnerEnemy::OnStunned()
{
	weapon_mechanics_->OnStunned();
	Super::OnStunned();
}
