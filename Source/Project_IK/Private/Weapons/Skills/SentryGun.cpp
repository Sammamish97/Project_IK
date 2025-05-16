/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.25.2025
Summary : Source file for Sentry Gun.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Weapons/Skills/SentryGun.h"

#include "Components/CapsuleComponent.h"
#include "Components/CharacterStatComponent.h"
#include "Components/ObjectPoolComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Weapons/Guns/Bullet.h"

// Sets default values
ASentryGun::ASentryGun()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("HeroPreset"));
	GetMesh()->SetCollisionProfileName(TEXT("NoCollision"));
	muzzle_ = CreateDefaultSubobject<USphereComponent>(TEXT("muzzle"));
	bullet_pool_ = CreateDefaultSubobject<UObjectPoolComponent>(TEXT("bullet_pool"));

	muzzle_->SetupAttachment(RootComponent);
}

void ASentryGun::BeginFire(AActor* target)
{
	float total_fire_per_sec = (1 + character_stat_component_->GetAttackSpeed() / 100.f);
	float weapon_attack_speed = 1.f / total_fire_per_sec;
	
	if(GetWorld()->GetTimerManager().IsTimerActive(fire_timer_handle_) == false && target)
	{
		FTimerDelegate fire_del = FTimerDelegate::CreateUObject(this, &ASentryGun::OnFire, target);
		GetWorld()->GetTimerManager().SetTimer(fire_timer_handle_, fire_del, weapon_attack_speed, true, weapon_attack_speed); 
	}
}

void ASentryGun::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	//1. 사거리 내 적이 있는지 체크.
	float min_distance = TNumericLimits<float>::Max();
	
	TArray<AActor*> ignore_actors;
	TArray<AActor*> out_actors;
	TArray<TEnumAsByte<EObjectTypeQuery>> traceObjectTypes;

	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetActorLocation(),
		character_stat_component_->GetSightRange(),
		traceObjectTypes, target_class_, ignore_actors, out_actors);
	
	AActor* nearest_actor = nullptr;
	for(const auto& elem : out_actors)
	{
		FVector owner_pos = GetActorLocation();
		FVector target_pos = elem->GetActorLocation();
		float cur_distance = FVector::DistSquared2D(owner_pos, target_pos);
		if(cur_distance < min_distance)
		{
			nearest_actor = elem;
			min_distance = cur_distance;
		}
	}
	//2. 적이 있다면 적 방향으로 사격.
	if (nearest_actor)
	{
		BeginFire(nearest_actor);
	}
	else
	{
		StopFire();
	}
}

void ASentryGun::OnFire(AActor* nearest_actor)
{
	if (nearest_actor)
	{
		FRotator rotation = UKismetMathLibrary::FindLookAtRotation(muzzle_->GetComponentLocation(), nearest_actor->GetActorLocation());
		FVector scale = object_pool_component_->GetObjectClass()->GetDefaultObject<AActor>()->GetRootComponent()->GetRelativeScale3D();
		FTransform spawn_transform(rotation, muzzle_->GetComponentLocation(), scale);
		ABullet* bullet = Cast<ABullet>(bullet_pool_->SpawnFromPool(spawn_transform));
		if (bullet)
		{
			bullet->SetShooter(this);
			FDamageData dmg_data = {20.f, 0, EDamageType::Projectile, this, nullptr};
			bullet->SetDamageData(dmg_data);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Spawning a bullet has failed!"));
		}
	}
}

void ASentryGun::StopFire()
{
	GetWorld()->GetTimerManager().ClearTimer(fire_timer_handle_);
}
