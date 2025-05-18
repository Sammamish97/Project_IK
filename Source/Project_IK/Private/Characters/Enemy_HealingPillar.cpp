/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.18.2025
Summary : Source file for Healing Pillar.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Characters/Enemy_HealingPillar.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Characters/Unit.h"


// Sets default values
AEnemy_HealingPillar::AEnemy_HealingPillar()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemy_HealingPillar::ActivateBuff()
{
	Super::ActivateBuff();
	//1. 범위 내 아군 찾기.
	TArray<AActor*> ignore_actors;
	TArray<AActor*> out_actors;
	TArray<TEnumAsByte<EObjectTypeQuery>> traceObjectTypes;
	traceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel2));
	

	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetActorLocation(),
		buff_range_,
		traceObjectTypes, AEnemyBase::StaticClass(), ignore_actors, out_actors);
	//2. 힐 주기.
	for (auto elem : out_actors)
	{
		TWeakObjectPtr<AActor> actor_ptr = elem;
		if (auto actor = actor_ptr.Get())
		{
			if (AUnit* casted_unit = Cast<AUnit>(actor))
			{
				casted_unit->Heal(heal_amount_);
			}
		}
	}
}
