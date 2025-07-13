/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.17.2025
Summary : Source file for Bullet Chain Effect Component.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Abilities/OnHitComponents/BulletChainEffectComponent.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Characters/Unit.h"

#include "Weapons/Guns/Bullet.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

void UBulletChainEffectComponent::OnHit(AActor* target)
{
	Super::OnHit(target);

	//1. 총알의 전도는 일단 유닛 하나가 총알에 맞고 시작한다. 해당 유닛은 대상에서 제외해야 한다.
	TArray<AActor*> visited;
	visited.Add(target);
	

	for (int32 i = 1; i < chain_amount_; ++i)
	{
		AActor* last_conducted = visited[i - 1];
		TArray<AActor*> out_actors;
		TArray<TEnumAsByte<EObjectTypeQuery>> traceObjectTypes;
		
		UKismetSystemLibrary::SphereOverlapActors(GetWorld(), last_conducted->GetActorLocation(),
			chain_radius_, traceObjectTypes, target_class_, visited, out_actors);

		if (out_actors.IsEmpty())
		{
			break;
		}
		
		AActor* nearest_actor = nullptr;
		float min_distance = TNumericLimits<float>::Max();

		for(const auto& elem : out_actors)
		{
			FVector owner_pos = last_conducted->GetActorLocation();
			FVector target_pos = elem->GetActorLocation();
			float cur_distance = FVector::DistSquared2D(owner_pos, target_pos);
			if(cur_distance < min_distance)
			{
				nearest_actor = elem;
				min_distance = cur_distance;
			}
		}
		visited.Add(nearest_actor);
	}
	
	//2. Visited array에 도탄될 대상이 전부 정해졌으면 도탄 효과를 발동한다.
	for (int32 i = 0; i < visited.Num(); ++i)
	{
		if (AUnit* cur_unit = Cast<AUnit>(visited[i]))
		{
			//도탄 데미지 전달.
			FDamageData dmg_data = {77.f, 0, EDamageType::Projectile, shooter_,cur_unit};
			cur_unit->GetDamage(dmg_data);
		}
	}
}

void UBulletChainEffectComponent::ApplyEffect(ABullet* bullet) const
{
	if (on_hit_effect_)
	{
		UNiagaraComponent* component = UNiagaraFunctionLibrary::SpawnSystemAttached(on_hit_effect_, bullet->GetSceneComponent(), NAME_None, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, false);
		component->SetVariableFloat(FName("SphereRadius"), 10.f);
	}
	if (on_hit_material_)
	{
		bullet->ApplyMaterial(0, on_hit_material_);
	}
}
