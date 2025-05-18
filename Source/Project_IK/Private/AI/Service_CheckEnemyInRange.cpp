/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.10.2024
Summary : Source file for Check Enemy In Range node.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "AI/Service_CheckEnemyInRange.h"

#include "Characters/Unit.h"
#include "AIController.h"
#include "Components/CharacterStatComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/Enemy_LaserDrone.h"
#include "Components/WeaponMechanics.h"
UService_CheckEnemyInRange::UService_CheckEnemyInRange()
{
	NodeName = "CheckEnemyInRange";
	Interval = 0.001f;
	RandomDeviation = 0.f;

	attack_target_key_.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UService_CheckEnemyInRange, attack_target_key_), UObject::StaticClass());
}

void UService_CheckEnemyInRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	AUnit* casted_gunner = Cast<AUnit>(OwnerComp.GetAIOwner()->GetPawn());
	if(	UObject* target = blackboard->GetValueAsObject(attack_target_key_.SelectedKeyName))
	{
		AActor* casted_actor = Cast<AActor>(target);
		float distance = FVector::Distance(casted_gunner->GetActorLocation(), casted_actor->GetActorLocation());
		if (is_drone_)
		{
			if (auto drone = Cast<AEnemy_LaserDrone>(casted_gunner))
			{
				if (drone->GetLaserRange() > distance)
				{
					blackboard->SetValueAsBool(is_enemy_in_range_key_.SelectedKeyName, true);
				}
				else
				{
					blackboard->SetValueAsBool(is_enemy_in_range_key_.SelectedKeyName, false);
				}
			}
		}
		else
		{
			if (auto weapon_mechanics = casted_gunner->GetComponentByClass<UWeaponMechanics>())
			{
				if (weapon_mechanics->GetWeaponData().fire_range > distance)
				{
					blackboard->SetValueAsBool(is_enemy_in_range_key_.SelectedKeyName, true);
				}
				else
				{
					blackboard->SetValueAsBool(is_enemy_in_range_key_.SelectedKeyName, false);
				}
			}
		}
	}
}