/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.03.2024
Summary : Source file for Gun.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Weapons/Guns/Gun.h"

#include "Characters/HeroBase.h"
#include "Components/ObjectPoolComponent.h"
#include "Components/BulletOnHitEffectComponent.h"
#include "Components/AudioComponent.h"
#include "NiagaraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Structs/DamageData.h"
#include "Weapons/Guns/Bullet.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	weapon_mesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunMesh"));
	object_pool_component_ = CreateDefaultSubobject<UObjectPoolComponent>(TEXT("ObjectPool"));
	weapon_mesh_->SetCollisionProfileName(TEXT("NoCollision"));
	muzzle_socket_name_ = TEXT("Muzzle");

	SetRootComponent(weapon_mesh_);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGun::Reload()
{
	Reload(weapon_data_.max_magazine);
}

void AGun::Reload(int32 amount)
{
	is_first_bullet_on_magazine_ = true;
	cur_magazine_ += amount;
}

void AGun::SpawnBullet(const FTransform& transform, const FDamageData& dmg_data)
{
	ABullet* bullet = Cast<ABullet>(object_pool_component_->SpawnFromPool(transform));
	if (is_first_bullet_on_magazine_)
	{
		is_first_bullet_on_magazine_ = false;
		for (auto& elem : on_hit_after_reload_)
		{
			bullet->AddOnHitComponent(elem);
		}
	}
	
	for (auto& elem : on_hit_effect_classes_)
	{
		bullet->AddOnHitComponent(elem);
	}
	if (bullet)
	{
		bullet->SetShooter(gun_owner_);
		bullet->SetDamageData(dmg_data);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Spawning a bullet has failed!"));
	}
}

void AGun::FireSingleBullet(FVector muzzle_location, FVector target_pos, FDamageData dmg_data)
{
	FRotator rotation = UKismetMathLibrary::FindLookAtRotation(muzzle_location, target_pos);
	FVector scale = object_pool_component_->GetObjectClass()->GetDefaultObject<AActor>()->GetRootComponent()->GetRelativeScale3D();
	FTransform spawn_transform(rotation, muzzle_location, scale);
	SpawnBullet(spawn_transform, dmg_data);
	cur_magazine_ -= 1;
}

void AGun::FireBuckShot(FVector muzzle_location, FVector target_pos, FDamageData dmg_data)
{
	float TEMP_DISTANCE_TO_SPHERE = 100;
	float TEMP_SPHERE_RADIUS = 10;

	FVector to_target_normalized = (target_pos - muzzle_location).GetSafeNormal();
	FVector sphere_center = muzzle_location + to_target_normalized * TEMP_DISTANCE_TO_SPHERE;

	int32 TEMP_SHOTGUN_PALLET = 5;
	for (int32 i = 0; i < TEMP_SHOTGUN_PALLET; ++i)
	{
		FVector randVec = UKismetMathLibrary::RandomUnitVector() * FMath::FRandRange(0.f, TEMP_SPHERE_RADIUS);
		FVector end_loc = sphere_center + randVec;
		
		FRotator rotation = UKismetMathLibrary::FindLookAtRotation(muzzle_location, end_loc);
		FVector scale = object_pool_component_->GetObjectClass()->GetDefaultObject<AActor>()->GetRootComponent()->GetRelativeScale3D();
		FTransform spawn_transform(rotation, muzzle_location, scale);
		SpawnBullet(spawn_transform, dmg_data);
	}
	cur_magazine_ -= 1;
}

void AGun::FireWeapon(FVector target_pos, FDamageData damage)
{
	if(cur_magazine_ > 0)
	{
		// @@ TODO: Need to discuss use it even though there are side effects.
		// While using AlwaysSpawn works, there might be Overlapping Actors, and GameplayMechanics 
		// 1. Overlapping Actors
		// It may cause physics glitches or visual artifacts
		// 2. Gameplay Mechanics
		// Spawn in obstructed areas might break immersion or functionality.
		// Such as enemies spawning inside walls.
		OnFireStub();
		auto muzzle_location = weapon_mesh_->GetSocketTransform(muzzle_socket_name_).GetLocation();
		if (weapon_data_.bullet_type == EBulletType::Buckshot)
		{
			FireBuckShot(muzzle_location, target_pos, damage);
		}
		else if (weapon_data_.bullet_type == EBulletType::FMJ)
		{
			FireSingleBullet(muzzle_location, target_pos, damage);
		}
	}
}

bool AGun::IsMagazineEmpty() const
{
	return cur_magazine_ <= 0;
}

void AGun::SetWeaponData(FWeaponData weapon_data)
{
	weapon_data_ = weapon_data;
	cur_magazine_ = weapon_data_.max_magazine;
	object_pool_component_->SetObjectClass(weapon_data_.bullet_class_);
	weapon_mesh_->SetStaticMesh(weapon_data_.weapon_mesh);
}

FWeaponData AGun::GetWeaponData()
{
	return weapon_data_;
}

void AGun::SetGunOwner(TWeakObjectPtr<AActor> gun_owner)
{
	gun_owner_ = gun_owner;
	//TODO: Gun이 AHeroBase 알아야 할까? 이게 최선은 아닐 것이다.
	bool is_hero = gun_owner_->IsA(AHeroBase::StaticClass());
	for (auto elem : object_pool_component_->GetObjectPool())
	{
		Cast<ABullet>(elem)->SetCollisionPreset(is_hero);
	}
	//TODO: 무기별로 애니메이션을 세팅하는 부분 역시 refactoring이 필요하다.
	//TODO: 그리고 이 코드는 의도대로 작동하지 않는다.
	Cast<ACharacter>(gun_owner_)->GetMesh()->AnimClass = anim_instance_class_;
}

void AGun::OnFireStub()
{
	// niagara_component_->SetAsset(weapon_data_.fire_muzzle_effect_);
	// niagara_component_->ActivateSystem();
	// audio_component_->SetSound(weapon_data_.fire_sound_);
	// audio_component_->Play();
}

void AGun::OnReloadStub()
{
	// audio_component_->SetSound(weapon_data_.reload_sound_);
	// audio_component_->Play();
}

void AGun::AddOnHitComponent(TSubclassOf<UBulletOnHitEffectComponent> target_component)
{
	on_hit_effect_classes_.Add(target_component);
}

void AGun::RemoveOnHitComponent(TSubclassOf<UBulletOnHitEffectComponent> target_component)
{
	on_hit_effect_classes_.Remove(target_component);
}

void AGun::ClearOnHitComponents()
{
	on_hit_effect_classes_.Empty();
}

void AGun::AddAfterReloadOnHitComponent(TSubclassOf<class UBulletOnHitEffectComponent> target_component)
{
	on_hit_after_reload_.Add(target_component);
}

void AGun::RemoveAfterReloadOnHitComponent(TSubclassOf<class UBulletOnHitEffectComponent> target_component)
{
	on_hit_after_reload_.Remove(target_component);
}

void AGun::ClearAfterReloadOnHitComponents()
{
	on_hit_after_reload_.Empty();
}
