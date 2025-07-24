/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.24.2025
Summary : Source file for WaitForStun Task.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "AI/Task_WaitForStun.h"

#include "AIController.h"
#include "Characters/Unit.h"

UTask_WaitForStun::UTask_WaitForStun()
{
	NodeName = "WaitForStun";
}

EBTNodeResult::Type UTask_WaitForStun::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(auto casted_unit = Cast<AUnit>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		return EBTNodeResult::InProgress;
	}
	return EBTNodeResult::Failed;
}
