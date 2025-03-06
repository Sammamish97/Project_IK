/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.05.2024
Summary : Source file for Find Nearest Enemy service node.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "AI/Service_FindNearestEnemy.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Class.h"
#include "Characters/EnemyBase.h"
#include "Characters/HeroBase.h"
#include "Characters/Unit.h"
#include "Components/CharacterStatComponent.h"
#include "Managers/EnumCluster.h"
#include "Kismet/KismetSystemLibrary.h"

UService_FindNearestEnemy::UService_FindNearestEnemy()
{
	NodeName = "FindNearestEnemy";
	Interval = 0.001f;
	RandomDeviation = 0.f;

	target_class_key_.AddClassFilter(this, GET_MEMBER_NAME_CHECKED(UService_FindNearestEnemy, target_class_key_), UObject::StaticClass());
	attack_target_key_.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UService_FindNearestEnemy, attack_target_key_), UObject::StaticClass());
}

void UService_FindNearestEnemy::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	AUnit* casted_gunner = Cast<AUnit>(OwnerComp.GetAIOwner()->GetPawn());

	float min_distance = TNumericLimits<float>::Max();
	if (blackboard) 
	{
		if (UClass* target_class = blackboard->GetValueAsClass(target_class_key_.SelectedKeyName)) {
			TArray<AActor*> ignore_actors;
			TArray<AActor*> out_actors;
			TArray<TEnumAsByte<EObjectTypeQuery>> traceObjectTypes;
			if(target_class == AHeroBase::StaticClass())
			{
				//ECC_GameTraceChannel1 == Hero Trace Channel.
				traceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel1));
			}
			else if(target_class == AEnemyBase::StaticClass())
			{
				//ECC_GameTraceChannel2 == Enemy Trace Channel.
				traceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel2));
			}

			UKismetSystemLibrary::SphereOverlapActors(GetWorld(), casted_gunner->GetActorLocation(),
				casted_gunner->GetCharacterStat()->GetSightRange(),
				traceObjectTypes, target_class, ignore_actors, out_actors);
			
			AActor* nearest_actor = nullptr;
			for(const auto& elem : out_actors)
			{
				FVector owner_pos = casted_gunner->GetActorLocation();
				FVector target_pos = elem->GetActorLocation();
				float cur_distance = FVector::DistSquared2D(owner_pos, target_pos);
				if(cur_distance < min_distance)
				{
					nearest_actor = elem;
					min_distance = cur_distance;
				}
			}
			
			if(nearest_actor != nullptr)
			{
				blackboard->SetValueAsObject(attack_target_key_.SelectedKeyName, nearest_actor);
			}
		}
	}
}
