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
	NodeName = "FindEnemy";
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
				if (AUnit* casted_unit = Cast<AUnit>(elem))
				{
					if (casted_unit->IsDead())
					{
						continue;
					}
				}
				FVector owner_pos = casted_gunner->GetActorLocation();
				FVector target_pos = elem->GetActorLocation();
				float cur_distance = FVector::Dist2D(owner_pos, target_pos);
				distance_object_pairs.Push({cur_distance, elem});
			}

			if (distance_object_pairs.IsEmpty() == true)
			{
				blackboard->SetValueAsObject(attack_target_key_.SelectedKeyName, nullptr);
				blackboard->SetValueAsBool(is_enemy_in_range_key_.SelectedKeyName, false);

				AAIController* owner_controller_ = OwnerComp.GetAIOwner();
				owner_controller_->SetFocus(nullptr);
				return;
			}
			
			AActor* target = nullptr;
			switch (static_cast<EAIFindTargetType>(blackboard->GetValueAsEnum(target_type_key_.SelectedKeyName)))
			{
			//만약 가장 가까운 적을 찾아야 한다면 가장 가까운 적을 찾는다.
			case EAIFindTargetType::Nearest:
				{
					distance_object_pairs.Sort();
					target = distance_object_pairs[0].Value;
				}
				break;

			//만약 가장 멀리있는 적을 찾아야 한다면 다음의 로직을 따라간다.
			//1. 시야 내 있는 적의 배열을 거리 내림차순 정렬 한다.
			//2. 가장 가까이 있는 적이 사거리의 2/3안에 있는지 확인한다. 만약 가장 가까운 적이 2/3보다 멀다면 nullptr로 set한다.
			//3. 가장 가까이 있는 적이 2/3거리 안에 있다면, 가장 멀리 있는 적을 attack target으로 set한다.
			case EAIFindTargetType::Farthest:
				{
					distance_object_pairs.Sort(TGreater());
					if (auto weapon_mechanics = casted_gunner->GetComponentByClass<UWeaponMechanics>())
					{
						float weapon_range = weapon_mechanics->GetWeaponData().fire_range;
						float nearest_dist = distance_object_pairs.Last().Key;
						if (weapon_range * 0.5 >= nearest_dist)
						{
							target = distance_object_pairs[0].Value;
						}
					}
				}
				break;
				
			case EAIFindTargetType::Random:
				target = distance_object_pairs[FMath::RandRange(0, FMath::Max(0, distance_object_pairs.Num()-1))].Value;
				break;
				
			case EAIFindTargetType::INVALID:
			default:
				break;
			}
			blackboard->SetValueAsObject(attack_target_key_.SelectedKeyName, target);
		}
	}
}