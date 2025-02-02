/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.08.2024
Summary : Source file for Self Explosion Enemy.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Characters/SelfExplosionEnemy.h"

#include "Components/CharacterStatComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Interfaces/Damageable.h"

ASelfExplosionEnemy::ASelfExplosionEnemy()
{
	explosion_start_radius_ = 100.f;
	explosion_radius_ = 500.f;
	//Delay는 아직 사용되고 있지 않다.
	explosion_delay_ = 1.f;
}

void ASelfExplosionEnemy::BeginPlay()
{
	Super::BeginPlay();
}

void ASelfExplosionEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASelfExplosionEnemy::Explosion()
{
	TArray<TEnumAsByte<EObjectTypeQuery>> traceObjectTypes;
	//ECC_GameTraceChannel1 == Hero Trace Channel.
	traceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1));

	
	UClass* seek_class = nullptr;
	TArray<AActor*> ignore_actors;
	TArray<AActor*> out_actors;

	UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetActorLocation(),
		explosion_radius_, traceObjectTypes, seek_class, ignore_actors, out_actors);

	DrawDebugSphere(GetWorld(), GetActorLocation(), explosion_radius_, 12, FColor::Red, false, 1.0f);
	for (AActor* overlappedActor : out_actors) {
		if(auto casted = Cast<IDamageable>(overlappedActor))
		{
			FDamageData data = {GetCharacterStat()->GetAttack(), EDamageType::Explosive, this};
			casted->GetDamage(data);
		}
	}

	Destroy();
}

float ASelfExplosionEnemy::GetExplosionDelay()
{
	return explosion_delay_;
}

float ASelfExplosionEnemy::GetExplosionRadius()
{
	return explosion_radius_;
}

float ASelfExplosionEnemy::GetExplosionStartRadius()
{
	return explosion_start_radius_;
}
