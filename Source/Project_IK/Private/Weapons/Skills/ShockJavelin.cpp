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
#include "Environments/Cover.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Interfaces/Damageable.h"

// Sets default values
AShockJavelin::AShockJavelin()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	collision_ = CreateDefaultSubobject<UBoxComponent>(FName("Sphere"));
	movement_ = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));
	javelin_mesh_ = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	javelin_mesh_->SetupAttachment(collision_);
	
	collision_->OnComponentBeginOverlap.AddDynamic(this, &AShockJavelin::OnOverlapBegin);
	collision_->SetCollisionProfileName(FName("HeroBulletPreset"));

	movement_->InitialSpeed = 1000.f;
	movement_->ProjectileGravityScale = 0.f;

	dmg_data_.atk_base_dmg = 100.f;
	dmg_data_.damage_type = EDamageType::Explosive;
	
	SetRootComponent(collision_);
}

void AShockJavelin::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IDamageable* casted_damage_logic = Cast<IDamageable>(OtherActor);
	dmg_data_.attack_target = OtherActor;
	if (OtherActor->IsA(ACover::StaticClass()))
	{
		dmg_data_.atk_base_dmg *= cover_dmg_scale_;
	}
	else
	{
		Cast<AUnit>(OtherActor)->GetStunned(stun_duration_);
	}
	if(casted_damage_logic) casted_damage_logic->GetDamage(dmg_data_);
	Destroy();
}

void AShockJavelin::SetDamageData(FDamageData dmg_data)
{
	dmg_data_ = dmg_data;
}
