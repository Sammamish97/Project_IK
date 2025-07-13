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

#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Weapons/Guns/Bullet.h"

void UBulletOnHitEffectComponent::OnHit(AActor* target)
{
}

void UBulletOnHitEffectComponent::ApplyEffect(ABullet* bullet_actor) const
{
	if (on_hit_effect_)
	{
		UNiagaraComponent* component = UNiagaraFunctionLibrary::SpawnSystemAttached(on_hit_effect_, bullet_actor->GetSceneComponent(), NAME_None, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, false);
	}
	if (on_hit_material_)
	{
		bullet_actor->ApplyMaterial(0, on_hit_material_);
	}
}
