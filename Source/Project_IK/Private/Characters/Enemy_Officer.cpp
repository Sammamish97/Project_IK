/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.28.2025
Summary : Source file for Enemy Officer.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Characters/Enemy_Officer.h"

#include "Kismet/GameplayStatics.h"
#include "Subsystems/DelegateBridgeSubsystem.h"
#include "WorldSettings/IKGameModeBase.h"

// Called when the game starts or when spawned
void AEnemy_Officer::BeginPlay()
{
	Super::BeginPlay();
	auto game_mode = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	auto delegate_bridge = GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>();
	for(auto& hero_elem : game_mode->GetHeroContainer())
	{
		if(hero_elem != nullptr)
		{
			delegate_bridge->BindOnHPChangedWithOwner(Cast<AUnit>(hero_elem)->GetCharacterStat(), this, &AEnemy_Officer::PointTarget);
		}
	}
}

void AEnemy_Officer::PointTarget(float hp_ratio, AActor* owner_actor)
{
	if(is_targeting_available_)
	{
		if(hp_ratio <= targeting_hp_threshold_)
		{
			//0. 애니메이션 재생
			PlayAnimMontage(pointing_animation_);
			//1. 범위 내 적군 탐지.
			UClass* target_class = AEnemyBase::StaticClass();
			TArray<AActor*> ignore_actors;
			TArray<AActor*> out_actors;
			TArray<TEnumAsByte<EObjectTypeQuery>> traceObjectTypes;
			//ECC_GameTraceChannel2 == Enemy Trace Channel.
			traceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel2));
			

			UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetActorLocation(),
				rally_range_,
				traceObjectTypes, target_class, ignore_actors, out_actors);
			
			//2. 적의 타겟을 owner_actor로 변경.
			for(const auto& elem : out_actors)
			{
				Cast<AUnit>(elem)->SetAttackTarget(owner_actor);
			}
			is_targeting_available_ = false;
		}
	}
}