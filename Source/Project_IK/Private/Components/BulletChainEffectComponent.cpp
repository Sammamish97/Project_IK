/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.17.2025
Summary : Source file for Bullet Chain Effect Component.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Components/BulletChainEffectComponent.h"

#include "Abilities/ActiveSkills/ATC_MagnetizedEffect.h"
#include "Characters/EnemyBase.h"
#include "Characters/HeroBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Characters/Unit.h"


// Sets default values for this component's properties
UBulletChainEffectComponent::UBulletChainEffectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UBulletChainEffectComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	if (GetOwner()->IsA(AHeroBase::StaticClass()))
	{
		target_class_ = AEnemyBase::StaticClass();
	}
	else
	{
		target_class_ = AHeroBase::StaticClass();
	}
}

// Called every frame
void UBulletChainEffectComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

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
			FDamageData dmg_data = {77.f, 0, EDamageType::Projectile, shooter_,cur_unit};
			cur_unit->GetDamage(dmg_data);
			if (auto magnetized_effect = cur_unit->FindComponentByClass<UATC_MagnetizedEffect>())
			{
				magnetized_effect->IncreaseStack();
			}
			else
			{
				cur_unit->AddComponentByClass(UATC_MagnetizedEffect::StaticClass(), false, cur_unit->GetTransform(), false);
			}
		}
	}
}
