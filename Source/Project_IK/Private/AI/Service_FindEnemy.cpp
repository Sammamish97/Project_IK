/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.05.2024
Summary : Source file for Find Nearest Enemy service node.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "AI/Service_FindEnemy.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Class.h"
#include "Characters/EnemyBase.h"
#include "Characters/HeroBase.h"
#include "Characters/Unit.h"
#include "Components/CharacterStatComponent.h"
#include "Managers/EnumCluster.h"
#include "Kismet/KismetSystemLibrary.h"

UService_FindEnemy::UService_FindEnemy()
{
	NodeName = "FindNearestEnemy";
	Interval = 0.001f;
	RandomDeviation = 0.f;

	target_class_key_.AddClassFilter(this, GET_MEMBER_NAME_CHECKED(UService_FindEnemy, target_class_key_), UObject::StaticClass());
	attack_target_key_.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UService_FindEnemy, attack_target_key_), UObject::StaticClass());
}

void UService_FindEnemy::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	AUnit* casted_gunner = Cast<AUnit>(OwnerComp.GetAIOwner()->GetPawn());

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
			
			TArray<TPair<float, AActor*>> distance_object_pairs;
			for(const auto& elem : out_actors)
			{
				FVector owner_pos = casted_gunner->GetActorLocation();
				FVector target_pos = elem->GetActorLocation();
				float cur_distance = FVector::DistSquared2D(owner_pos, target_pos);
				distance_object_pairs.Push({cur_distance, elem});
			}

			switch (static_cast<EAIFindTargetType>(blackboard->GetValueAsEnum(target_type_key_.SelectedKeyName)))
			{
			case EAIFindTargetType::Nearest:
				distance_object_pairs.Sort();
				break;

			case EAIFindTargetType::Farthest:
				distance_object_pairs.Sort(TGreater<>());
				break;

			//IKTODO: 이 함수는 매 프레임 반드시 불린다.
			//그러므로, Random한 적을 찾는 로직을 다음과 같이 짜면 매 프레임 attack target이 바뀐다.
			//만약 Random한 적을 찾는 로직이 필요하다면, Attack Target이 없을 때 만 Random한 적을 찾는 로직을 추가해야한다.
			case EAIFindTargetType::Random:
				//distance_object_pairs[FMath::RandRange(0, FMath::Max(0, distance_object_pairs.Num()-1))];
				break;
				
			case EAIFindTargetType::Weakest:
				//IKTODO: 이후 추가.
				break;

			case EAIFindTargetType::INVALID:
			default:
				break;
			}
			
			if (distance_object_pairs.IsEmpty() == false)
			{
				blackboard->SetValueAsObject(attack_target_key_.SelectedKeyName, distance_object_pairs[0].Value);
			}
			else
			{
				blackboard->SetValueAsObject(attack_target_key_.SelectedKeyName, nullptr);
			}
		}
	}
}