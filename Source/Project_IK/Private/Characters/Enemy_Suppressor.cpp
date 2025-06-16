/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.30.2025
Summary : Source file for Suppressor enemy.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Characters/Enemy_Suppressor.h"
#include "Components/WeaponMechanics.h"
#include "Structs/BuffStatusData.h"
// Sets default values
AEnemy_Suppressor::AEnemy_Suppressor()
{
	weapon_mechanics_ = CreateDefaultSubobject<UWeaponMechanics>(TEXT("WeaponMechanics"));
}

void AEnemy_Suppressor::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemy_Suppressor::OnStunned()
{
	Super::OnStunned();
	//weapon_mechanics_->OnStunned();
}

void AEnemy_Suppressor::Die()
{
	Super::Die();
}

void AEnemy_Suppressor::OnEnterBattleOnce()
{
	Super::OnEnterBattleOnce();
	FTimerDelegate timer_delegate = FTimerDelegate::CreateUObject(this, &AEnemy_Suppressor::GetBonusPower);
	GetWorld()->GetTimerManager().SetTimer(preheat_timer_, timer_delegate, preheat_duration_, false);
}

void AEnemy_Suppressor::GetBonusPower()
{
}

void AEnemy_Suppressor::Attack(AActor* target)
{
	Super::Attack(target);
	weapon_mechanics_->BeginFire(target);
}