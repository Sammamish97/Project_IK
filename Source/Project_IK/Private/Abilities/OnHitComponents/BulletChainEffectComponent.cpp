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
#include "Components/CharacterStatComponent.h"
#include "Components/WeaponMechanics.h"
#include "Structs/WeaponStatusData.h"

#include "Subsystems/AudioManagerSubsystem.h"
#include "Subsystems/RandomNumberGeneratorSubsystem.h"

void UBulletChainEffectComponent::OnHit(AActor* target, const FHitResult& hit_result)
{
	Super::OnHit(target, hit_result);

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
	FDamageData dmg_data = GetOwner<ABullet>()->GetDamageData();
	for (int32 i = 0; i < visited.Num(); ++i)
	{
		if (AUnit* cur_unit = Cast<AUnit>(visited[i]))
		{
			//도탄 데미지 감쇄 & 전달.
			dmg_data.atk_base_dmg_ = dmg_data.atk_base_dmg_ * (1 - bounce_dmg_diminish_amount * (i + 1));
			cur_unit->GetDamage(dmg_data);
		}
	}

	PlaySFX(visited);
}

void UBulletChainEffectComponent::PlaySFX(const TArray<AActor*>& chained_actors)
{
	if (chained_actors.Num() - 1 < 0)
	{
		return;
	}

	for (int32 i = 1; i < chained_actors.Num(); i++)
	{
		FTimerHandle audio_timer;

		AActor* target = chained_actors[i];
		if (target)
		{
			GetWorld()->GetTimerManager().SetTimer(audio_timer, [&, target]() {

				float rand_pitch = URandomNumberGeneratorSubsystem::GetRNG(GetWorld()).RandRange(0.5f, 1.5f);
				UAudioManagerSubsystem::Get(this)->PlayAtLocation(EAudioType::Ricochet, target->GetActorLocation(), 1.f, rand_pitch);

				}, 0.1f * i, false);
		}
	}
}
