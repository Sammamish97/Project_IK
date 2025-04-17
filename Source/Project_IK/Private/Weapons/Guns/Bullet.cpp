/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.03.2024
Summary : Source file for Bullet.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Weapons/Guns/Bullet.h"

#include "Components/BulletOnHitEffectComponent.h"
#include "Interfaces/Damageable.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	collision_ = CreateDefaultSubobject<USphereComponent>(FName("Sphere"));
	movement_ = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));
	bullet_mesh_ = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	bullet_mesh_->SetupAttachment(collision_);
	
	collision_->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlapBegin);
	movement_->InitialSpeed = 1000.f;
	movement_->ProjectileGravityScale = 0.f;
	
	SetRootComponent(collision_);
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
}

void ABullet::SetInUse(bool in_use)
{
	Super::SetInUse(in_use);
	if(in_use_)
	{
		movement_->Velocity = GetActorForwardVector() * movement_->InitialSpeed;
	}
	else
	{
		movement_->Velocity = FVector::ZeroVector;
	}
}

void ABullet::SetCollisionPreset(bool is_hero)
{
	if (is_hero)
	{
		collision_->SetCollisionProfileName(FName("HeroBulletPreset"));
	}
	else
	{
		collision_->SetCollisionProfileName(FName("EnemyBulletPreset"));
	}
}

void ABullet::AddOnHitComponent(TSubclassOf<UBulletOnHitEffectComponent> target_class)
{
	UBulletOnHitEffectComponent* new_on_hit_component = NewObject<UBulletOnHitEffectComponent>(this, target_class);
	new_on_hit_component->RegisterComponent();
	on_hit_components_.Add(new_on_hit_component);
}

void ABullet::RemoveOnHitComponent(TSubclassOf<UBulletOnHitEffectComponent> target_class)
{
	for (const auto& elem : on_hit_components_)
	{
		if (elem.GetClass() == target_class)
		{
			on_hit_components_.Remove(elem);
			return;
		}
	}
}

void ABullet::ClearOnHitComponents()
{
	on_hit_components_.Empty();
}

void ABullet::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IDamageable* casted_damage_logic = Cast<IDamageable>(OtherActor);
	dmg_data_.attack_target = OtherActor;
	if(casted_damage_logic) casted_damage_logic->GetDamage(dmg_data_);
	for (const auto& elem : on_hit_components_)
	{
		elem->OnHit(OtherActor);
	}
	ClearOnHitComponents();
	ReturnToPool();
}

void ABullet::SetShooter(TWeakObjectPtr<AActor> shooter)
{
	shooter_ = shooter;
}

void ABullet::SetDamageData(FDamageData data)
{
	dmg_data_ = data;
}
