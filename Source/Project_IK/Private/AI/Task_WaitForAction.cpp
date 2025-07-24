/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.24.2025
Summary : Source file for Wait for active skill casting Task.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "AI/Task_WaitForAction.h"
#include "AIController.h"
#include "Characters/Unit.h"

UTask_WaitForAction::UTask_WaitForAction()
{
	NodeName = L"WaitForAction";
}

EBTNodeResult::Type UTask_WaitForAction::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(auto casted_unit = Cast<AUnit>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		casted_unit->OnFinishAction.AddDynamic(this, &UTask_WaitForAction::OnFinishAction);
		return EBTNodeResult::InProgress;
	}
	return EBTNodeResult::Failed;
}

EBTNodeResult::Type UTask_WaitForAction::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FinishLatentAbort(OwnerComp);
	return Super::AbortTask(OwnerComp, NodeMemory);
}

void UTask_WaitForAction::OnFinishAction(UBehaviorTreeComponent* bt_component, bool is_interrupted)
{
	if(auto casted_unit = Cast<AUnit>(bt_component->GetAIOwner()->GetPawn()))
	{
		casted_unit->OnFinishAction.AddDynamic(this, &UTask_WaitForAction::OnFinishAction);
	}
	FinishLatentTask(*bt_component, is_interrupted ? EBTNodeResult::Failed : EBTNodeResult::Succeeded);
}
