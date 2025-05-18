/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.18.2025
Summary : Source file for Laser drone enemy.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Characters/Enemy_LaserDrone.h"

// Sets default values
AEnemy_LaserDrone::AEnemy_LaserDrone()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemy_LaserDrone::BeginPlay()
{
	Super::BeginPlay();
}

float AEnemy_LaserDrone::GetLaserRange() const
{
	return laser_range_;
}

void AEnemy_LaserDrone::Attack(AActor* target)
{
	TWeakObjectPtr<AActor> target_ptr = target;
	if (auto target_actor = target_ptr.Get())
	{
		Super::Attack(target_actor);
		IDamageable* casted_damage_logic = Cast<IDamageable>(target_actor);

		FDamageData damage_data = FDamageData(laser_damage_, 0.f, EDamageType::Projectile, this, target_actor, false);
		casted_damage_logic->GetDamage(damage_data);
		DrawDebugLine(GetWorld(), GetMesh()->GetSocketTransform(muzzle_socket_name).GetLocation(), target_actor->GetActorLocation(), FColor::Purple, false, -1, 0, 5);
	}
}
