/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.22.2025
Summary : Source file for Mini Bullet.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Weapons/SetBonus/MiniBullet.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Interfaces/Damageable.h"
// Sets default values
AMiniBullet::AMiniBullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	collision_ = CreateDefaultSubobject<UBoxComponent>(FName("Sphere"));
	movement_ = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));
	mesh_ = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	mesh_->SetupAttachment(collision_);
	
	collision_->OnComponentBeginOverlap.AddDynamic(this, &AMiniBullet::OnOverlapBegin);
	collision_->SetCollisionProfileName(FName("HeroBulletPreset"));

	movement_->InitialSpeed = 1000.f;
	movement_->ProjectileGravityScale = 0.f;

	dmg_data_.atk_base_dmg = 100.f;
	dmg_data_.damage_type = EDamageType::Projectile;
	
	SetRootComponent(collision_);
}

void AMiniBullet::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	TWeakObjectPtr<AActor> actor_ptr = OtherActor;
	if (AActor* target = actor_ptr.Get())
	{
		Cast<IDamageable>(target)->GetDamage(dmg_data_);
	}
    Destroy();
}

void AMiniBullet::SetDamageData(FDamageData dmg_data)
{
	dmg_data_ = dmg_data;
}
