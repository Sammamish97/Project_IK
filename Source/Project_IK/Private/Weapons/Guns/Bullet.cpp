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

#include "NiagaraFunctionLibrary.h"
#include "Characters/Unit.h"

// Sets default values
ABullet::ABullet()
	: APooledActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	collision_ = CreateDefaultSubobject<USphereComponent>(FName("Sphere"));
	movement_ = CreateDefaultSubobject<UProjectileMovementComponent>(FName("ProjectileMovement"));
	bullet_mesh_ = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	bullet_mesh_->SetupAttachment(collision_);
	bullet_mesh_->SetCollisionProfileName(FName("NoCollision"));

	collision_->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlapBegin);
	collision_->SetCollisionProfileName(FName("HeroBulletPreset"));
	movement_->InitialSpeed = 1000.f;
	movement_->ProjectileGravityScale = 0.f;

	SetRootComponent(collision_);
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();

	original_material_ = bullet_mesh_->GetMaterial(0);
}

void ABullet::ClearComponentsAttachedOnMesh()
{
	TArray<USceneComponent*> attached_components;
	bullet_mesh_->GetChildrenComponents(true, attached_components);

	for (USceneComponent* component : attached_components)
	{
		if (component)
		{
			component->Deactivate();
			component->DestroyComponent();
		}
	}
}

void ABullet::SpawnImpactParticle(FVector impact_location, FVector impact_normal, const FDamageData& damage_data)
{
	UNiagaraSystem* impact_particle = nullptr;
	if (Cast<AUnit>(damage_data.attack_target_))
	{
		impact_particle = (damage_data.atk_base_dmg_ >= damage_data.skill_power_base_dmg_) ? attack_impact_particle_ : magic_impact_particle_;
	}
	else
	{
		impact_particle = concrete_impact_particle_;
	}
	
	if (impact_particle)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, impact_particle, impact_location, impact_normal.ToOrientationRotator());
	}
}

void ABullet::SetInUse(bool in_use)
{
	Super::SetInUse(in_use);
	if (in_use_)
	{
		movement_->Velocity = GetActorForwardVector() * movement_->InitialSpeed;
	}
	else
	{
		movement_->Velocity = FVector::ZeroVector;
	}
}

USceneComponent* ABullet::GetSceneComponent() const
{
	return bullet_mesh_;
}

void ABullet::ApplyMaterial(int32 element_index, UMaterialInterface* material)
{
	bullet_mesh_->SetMaterial(element_index, material);
}

void ABullet::ReturnToPool()
{
	Clear();
	Super::ReturnToPool();
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
	new_on_hit_component->ApplyEffect(this);
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

void ABullet::Clear()
{
	on_hit_components_.Empty();

	ClearComponentsAttachedOnMesh();

	UMaterialInterface* material = original_material_.Get();
	if (material)
	{
		bullet_mesh_->SetMaterial(0, material);
	}
}

void ABullet::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IDamageable* casted_damage_logic = Cast<IDamageable>(OtherActor);
	dmg_data_.attack_target_ = OtherActor;
	if (casted_damage_logic) casted_damage_logic->GetDamage(dmg_data_);
	for (const auto& elem : on_hit_components_)
	{
		elem->OnHit(OtherActor);
	}
	SpawnImpactParticle(SweepResult.ImpactPoint, SweepResult.ImpactNormal, dmg_data_);
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
