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
#include "NiagaraComponent.h"

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

void ABullet::AttachParticleEffects(const TArray<UNiagaraSystem*>& niagara_systems,
	const TMap<UNiagaraSystem*, TMap<FName, float>>& float_parameters,
	const TMap<UNiagaraSystem*, TMap<FName, FVector>>& vector_parameters)
{
	for (UNiagaraSystem* system : niagara_systems)
	{
		UNiagaraComponent* component = UNiagaraFunctionLibrary::SpawnSystemAttached(system, bullet_mesh_, NAME_None, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, false);

		// Send user parameters
		if (component)
		{
			if (const TMap<FName, float>* float_map = float_parameters.Find(system))
			{
				for (const TPair<FName, float>& pair : *float_map)
				{
					component->SetVariableFloat(pair.Key, pair.Value);
				}
			}

			if (const TMap<FName, FVector>* vector_map = vector_parameters.Find(system))
			{
				for (const TPair<FName, FVector>& pair : *vector_map)
				{
					component->SetVariableVec3(pair.Key, pair.Value);
				}
			}
		}

		component->Activate(true);
	}
}

void ABullet::ApplyMaterials(const TArray<UMaterialInterface*>& materials)
{
	for (int32 i = 0; i < materials.Num(); i++)
	{
		bullet_mesh_->SetMaterial(i, materials[i]);
	}
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
