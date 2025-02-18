/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.08.2025
Summary : Source file for Pistol.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Weapons/Guns/Pistol.h"
#include "Weapons/Guns/Bullet.h"

#include "Characters/HeroBase.h"
#include "Components/ObjectPoolComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
APistol::APistol()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void APistol::FireWeapon(FVector target_pos, FDamageData damage)
{
	Super::FireWeapon(target_pos, damage);
	if(cur_megazine_ > 0)
	{
		// @@ TODO: Need to discuss use it even though there are side effects.
		// While using AlwaysSpawn works, there might be Overlapping Actors, and GameplayMechanics 
		// 1. Overlapping Actors
		// It may cause physics glitches or visual artifacts
		// 2. Gameplay Mechanics
		// Spawn in obstructed areas might break immersion or functionality.
		// Such as enemies spawning inside walls.

		FRotator rotation = UKismetMathLibrary::FindLookAtRotation(muzzle_->GetComponentLocation(), target_pos);
		FVector scale = object_pool_component_->GetObjectClass()->GetDefaultObject<AActor>()->GetRootComponent()->GetRelativeScale3D();
		FTransform spawn_transform(rotation, muzzle_->GetComponentLocation(), scale);
		ABullet* bullet = Cast<ABullet>(object_pool_component_->SpawnFromPool(spawn_transform));
		if (bullet)
		{
			bullet->SetShooter(gun_owner_);
			bullet->SetDamageData(damage);
			cur_megazine_--;
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Spawning a bullet has failed!"));
		}
	}}
