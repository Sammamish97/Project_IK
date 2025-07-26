/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.18.2025
Summary : Source file for Shock Javelin.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Weapons/Skills/ShockJavelin.h"

#include "Characters/Unit.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Interfaces/Damageable.h"

#include "NiagaraComponent.h"

// Sets default values
AShockJavelin::AShockJavelin()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collision_ = CreateDefaultSubobject<UBoxComponent>(FName("Sphere"));
	movement_ = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));
	particle_system_ = CreateDefaultSubobject<UNiagaraComponent>(FName("Particles"));

	collision_->OnComponentBeginOverlap.AddDynamic(this, &AShockJavelin::OnOverlapBegin);
	collision_->SetCollisionProfileName(FName("HeroBulletPreset"));

	movement_->InitialSpeed = 5000.f;
	movement_->ProjectileGravityScale = 0.f;

	particle_system_->SetupAttachment(collision_);

	SetRootComponent(collision_);
}

void AShockJavelin::Tick(float DeltaSeconds)
{
	if (has_dispatched_)
	{
		return;
	}
	Super::Tick(DeltaSeconds);

	timer_ += DeltaSeconds;
	if (timer_ < casting_time_)
	{
		// Spawning a shock javelin
		particle_system_->SetFloatParameter(FName("User.Javelin Length"), FMath::Lerp(0.f, javelin_length_, timer_ / casting_time_));
	}
	else
	{
		// Dispatch the javelin
		particle_system_->SetFloatParameter(FName("User.Javelin Length"), javelin_length_);
		movement_->Velocity = GetActorForwardVector() * movement_->InitialSpeed;
		movement_->Activate();
		has_dispatched_ = true;
	}
}

void AShockJavelin::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IDamageable* casted_damage_logic = Cast<IDamageable>(OtherActor);

	// Overlapped on Cover or Characters.
	if (casted_damage_logic)
	{
		dmg_data_.attack_target_ = OtherActor;
		Cast<AUnit>(OtherActor)->GetStunned(stun_duration_);
		casted_damage_logic->GetDamage(dmg_data_);
		Destroy();
	}
}

void AShockJavelin::SetCastingTime(float casting_time)
{
	casting_time_ = casting_time;
}

void AShockJavelin::SetDamageData(const FDamageData& dmg_data)
{
	dmg_data_ = dmg_data;
}

void AShockJavelin::BeginPlay()
{
	Super::BeginPlay();

	movement_->Deactivate();
}
