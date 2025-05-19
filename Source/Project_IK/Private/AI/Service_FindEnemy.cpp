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
#include "Components/WeaponMechanics.h"
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
		if (blackboard->GetValueAsObject(attack_target_key_.SelectedKeyName) == nullptr)
		{
			//IKTODO: 새로운 적을 찾아야 한다면 발사를 멈춘다. 공격은 timer로 loop하기 때문이다. 더 좋은 방법이 있을 것이다.
			if (auto weapon_mechanics = casted_gunner->GetComponentByClass<UWeaponMechanics>())
			{
				weapon_mechanics->FinishFire();
			}
			if (UClass* target_class = blackboard->GetValueAsClass(target_class_key_.SelectedKeyName))
			{
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
}