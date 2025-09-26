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

	mesh_base_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	mesh_base_->SetupAttachment(RootComponent);
	mesh_attack_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Attack Mesh"));
	mesh_attack_->SetupAttachment(RootComponent);

	muzzle_->SetupAttachment(mesh_attack_);
}

void ASentryGun::InitSentryGun(bool is_upgraded, float skill_power)
{
	float extra_hp = skill_power * hit_points_scaling_factor_;
	float extra_skill_power = skill_power;
	if (is_upgraded)
	{
		extra_hp *= 1.2;
		extra_skill_power *= 1.2;
	}
	FStatusData extra_status;
	extra_status.hit_point_ = extra_hp;
	extra_status.skill_power_ = extra_skill_power;
	GetCharacterStat()->ApplyExtraStatusForSummoned(extra_status);
}

void ASentryGun::BeginFire(AActor* target)
{
	float total_fire_per_sec = (1 + character_stat_component_->GetAttackSpeed() / 100.f);
	float weapon_attack_speed = 1.f / total_fire_per_sec;
	
	if(GetWorld()->GetTimerManager().IsTimerActive(fire_timer_handle_) == false && target)
	{
		OnFire(target, weapon_attack_speed);
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
			AUnit* unit = Cast<AUnit>(elem);
			if (unit && unit->IsDead() == false)
			{
				nearest_actor = elem;
				min_distance = cur_distance;
			}
		}
	}
	//2. 적이 있다면 적 방향으로 사격.
	if (nearest_actor)
	{
		RotateMeshToTarget(nearest_actor);
		BeginFire(nearest_actor);
	}
	else
	{
		float rotation_speed = 360.f / 2.f;
		float delta_rotation = rotation_speed * DeltaSeconds;

		FRotator rotator = mesh_attack_->GetComponentRotation();
		rotator.Yaw += delta_rotation;
		mesh_attack_->SetWorldRotation(rotator);

		StopFire();
	}
}

void ASentryGun::OnFire(AActor* target, float attack_speed)
{
	AUnit* unit = Cast<AUnit>(target);
	if (unit && unit->IsDead() == false)
	{
		FRotator rotation = UKismetMathLibrary::FindLookAtRotation(muzzle_->GetComponentLocation(), target->GetActorLocation());
		ABullet* bullet = Cast<ABullet>(bullet_pool_->SpawnFromPool(rotation, muzzle_->GetComponentLocation()));
		if (bullet)
		{
			bullet->SetShooter(this);
			FDamageData dmg_data = {0.f, GetCharacterStat()->GetSkillPower() * dmg_scaling_factor_, EDamageType::Projectile, this, nullptr};
			bullet->SetDamageData(dmg_data);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Spawning a bullet has failed!"));
		}

		FTimerDelegate fire_del = FTimerDelegate::CreateUObject(this, &ASentryGun::OnFire, target, attack_speed);
		GetWorld()->GetTimerManager().SetTimer(fire_timer_handle_, fire_del, attack_speed, false);
	}
}

void ASentryGun::StopFire()
{
	GetWorld()->GetTimerManager().ClearTimer(fire_timer_handle_);
}

void ASentryGun::RotateMeshToTarget(AActor* target)
{
	FVector my_location = GetActorLocation();
	FVector target_location = target->GetActorLocation();

	FVector direction = target_location - my_location;
	direction.Z = 0.f;
	direction.Normalize();

	FRotator target_rotation = direction.Rotation();

	FRotator new_rotation(0.f, target_rotation.Yaw, 0.f);

	mesh_attack_->SetWorldRotation(new_rotation);
}
