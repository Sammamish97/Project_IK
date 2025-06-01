/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.17.2024
Summary : Source file for BeginFire Task.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "AI/Task_BeginFire.h"

#include "AIController.h"
#include "Components/WeaponMechanics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Interfaces/Attackable.h"

UTask_BeginFire::UTask_BeginFire()
{
	NodeName = "Begin Fire";
}

EBTNodeResult::Type UTask_BeginFire::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();

	TWeakObjectPtr<APawn> casted_pawn_ptr = OwnerComp.GetAIOwner()->GetPawn();
	if (auto casted_pawn = casted_pawn_ptr.Get())
	{
		if (auto casted_attackable_unit = Cast<IAttackable>(casted_pawn))
		{
			TWeakObjectPtr target_ptr = blackboard->GetValueAsObject(attack_target_key_.SelectedKeyName);
			if(UObject* casted_target =target_ptr.Get())
			{
				casted_attackable_unit->Attack(Cast<AActor>(casted_target));
				return EBTNodeResult::Succeeded;
				//IKTODO: 로직과 코스트 상 InProgress를 쓰는것이 더 좋을 수 있으나, 개발 코스트가 커질 수 있다. 그러므로 일단 간단한 버전으로 구현한다.
				//return EBTNodeResult::InProgress;
			}
		}
	}
	return EBTNodeResult::Failed;
}

EBTNodeResult::Type UTask_BeginFire::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (auto casted_pawn = OwnerComp.GetAIOwner()->GetPawn())
	{
		auto component = casted_pawn->GetComponentByClass(UWeaponMechanics::StaticClass()); 
		if(auto casted_component = Cast<UWeaponMechanics>(component))
		{
			casted_component->FinishFire();
			return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}
