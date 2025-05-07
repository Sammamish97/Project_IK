/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.1.2025
Summary : Source file for Update Unit State Task.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "AI/Task_UpdateUnitState.h"

#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UTask_UpdateUnitState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	blackboard->SetValueAsEnum(unit_state_key_.SelectedKeyName, static_cast<uint8>(new_state_));
	return EBTNodeResult::Succeeded;
}