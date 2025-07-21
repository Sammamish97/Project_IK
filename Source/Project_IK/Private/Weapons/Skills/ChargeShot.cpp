/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 07.12.2025
Summary : Source file for an actor of charge shot skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Weapons/Skills/ChargeShot.h"

#include "Characters/Unit.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "Environments/Cover.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Interfaces/Damageable.h"

#include "NiagaraComponent.h"

// Sets default values
AChargeShot::AChargeShot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collision_ = CreateDefaultSubobject<UBoxComponent>(FName("Sphere"));
	movement_ = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));
	particle_system_ = CreateDefaultSubobject<UNiagaraComponent>(FName("Particles"));

	collision_->OnComponentBeginOverlap.AddDynamic(this, &AChargeShot::OnOverlapBegin);
	collision_->SetCollisionProfileName(FName("HeroBulletPreset"));

	movement_->InitialSpeed = 1000.f;
	movement_->ProjectileGravityScale = 0.f;

	particle_system_->SetupAttachment(collision_);

	SetRootComponent(collision_);
}

void AChargeShot::SetDamageData(const FDamageData& dmg_data)
{
	dmg_data_ = dmg_data;
}

void AChargeShot::SetCastingTime(float casting_time)
{
	casting_time_ = casting_time;
}

// Called when the game starts or when spawned
void AChargeShot::BeginPlay()
{
	Super::BeginPlay();
	
	movement_->Deactivate();
}

// Called every frame
void AChargeShot::Tick(float DeltaTime)
{
	if (has_dispatched_)
	{
		return;
	}

	Super::Tick(DeltaTime);

	timer_ += DeltaTime;
	if (timer_ < casting_time_)
	{
		// Spawning a charge shot
	}
	else
	{
		// Dispatch the charge shot
		movement_->Velocity = GetActorForwardVector() * movement_->InitialSpeed;
		movement_->Activate();
		has_dispatched_ = true;
	}
}

void AChargeShot::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IDamageable* casted_damage_logic = Cast<IDamageable>(OtherActor);

	// Overlapped on Cover or Characters.
	if (casted_damage_logic)
	{
		dmg_data_.attack_target_ = OtherActor;
		casted_damage_logic->GetDamage(dmg_data_);
		Destroy();
	}
}

