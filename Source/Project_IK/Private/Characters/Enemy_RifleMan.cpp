/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.20.2024
Summary : Source file for rifle man enemy.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Characters/Enemy_RifleMan.h"

#include "Components/CharacterStatComponent.h"
#include "Components/WeaponMechanics.h"

AEnemy_RifleMan::AEnemy_RifleMan()
{
	weapon_mechanics_ = CreateDefaultSubobject<UWeaponMechanics>(TEXT("WeaponMechanics"));
}

void AEnemy_RifleMan::BeginPlay()
{
	Super::BeginPlay();
	weapon_mechanics_->EquipWeapon(EWeaponType::DefaultPistol);
}

void AEnemy_RifleMan::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AEnemy_RifleMan::Die()
{
	weapon_mechanics_->OnDestroy();
	Super::Die();
}

void AEnemy_RifleMan::OnStunned()
{
	UE_LOG(LogTemp, Warning, TEXT("AEnemy_RifleMan Stunned"));
	Super::OnStunned();
	weapon_mechanics_->OnStunned();
}

FDamageData AEnemy_RifleMan::Attack(AActor* target)
{
	FDamageData damage_data;
	damage_data.damage_type = EDamageType::Projectile;
	damage_data.attacker = this;
	weapon_mechanics_->SetDamageData(GetCharacterStat()->GetCharacterData(), damage_data);
	weapon_mechanics_->BeginFire(target);
	
	return damage_data;
}
