/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.17.2025
Summary : Source file for Bullet On Hit Effect Component.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Components/BulletOnHitEffectComponent.h"
#include "Characters/EnemyBase.h"
#include "Characters/HeroBase.h"

// Called when the game starts
void UBulletOnHitEffectComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner()->IsA(AHeroBase::StaticClass()))
	{
		target_class_ = AEnemyBase::StaticClass();
	}
	else
	{
		target_class_ = AHeroBase::StaticClass();
	}
}

void UBulletOnHitEffectComponent::OnHit(AActor* target)
{
}
