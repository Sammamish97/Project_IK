/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 05.30.2025
Summary : Source file for dagger projectiles.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Weapons/Runes/DaggerProjectiles.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "NiagaraComponent.h"

ADaggerProjectiles::ADaggerProjectiles()
	: ABullet()
{
	bullet_mesh_->SetVisibility(false, true);
	bullet_mesh_->SetSimulatePhysics(false);
	bullet_mesh_->PrimaryComponentTick.bCanEverTick = false;

	niagara_ = CreateDefaultSubobject<UNiagaraComponent>(FName("NiagaraParticleComponent"));
	niagara_->SetupAttachment(collision_);
}

void ADaggerProjectiles::BeginDaggerMovements()
{
	movement_->Deactivate();
	niagara_->Activate(true);
	GetWorldTimerManager().SetTimer(dagger_timer_, this, &ADaggerProjectiles::StartBackwardMotion, summon_times_, false);
}

void ADaggerProjectiles::BeginPlay()
{
	Super::BeginPlay();

	init_speed_ = movement_->InitialSpeed;
	niagara_->Deactivate();
}

void ADaggerProjectiles::StartBackwardMotion()
{
	movement_->Velocity = -GetActorForwardVector() * (init_speed_ / 100.f);
	movement_->Activate();
	GetWorldTimerManager().SetTimer(dagger_timer_, this, &ADaggerProjectiles::LaunchForward, backward_times_, false);
}

void ADaggerProjectiles::LaunchForward()
{
	movement_->Velocity = GetActorForwardVector() * init_speed_;
	//movement_->Velocity = GetActorForwardVector() * init_speed_;
	//movement_->InitialSpeed = init_speed_;
}
