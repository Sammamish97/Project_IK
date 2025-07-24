/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.24.2025
Summary : Source file for Wait for active skill casting Task.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "AI/Task_WaitForActiveSkill.h"
#include "AIController.h"
#include "Characters/Unit.h"
#include "Components/ActiveSkillMechanics.h"

UTask_WaitForActiveSkill::UTask_WaitForActiveSkill()
{
	NodeName = L"WaitForActiveSkillCasting";
}

EBTNodeResult::Type UTask_WaitForActiveSkill::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if(auto casted_unit = Cast<AUnit>(OwnerComp.GetAIOwner()->GetPawn()))
	{
		WaitForMessage(OwnerComp, TEXT("CastingFinished"), casted_unit->GetActionRequestID());
		return EBTNodeResult::InProgress;
	}
	return EBTNodeResult::Failed;
}
