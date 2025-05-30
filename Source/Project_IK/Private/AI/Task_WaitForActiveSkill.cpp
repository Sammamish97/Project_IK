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
#include "Abilities/SkillContainer.h"

UTask_WaitForActiveSkill::UTask_WaitForActiveSkill()
{
	NodeName = L"WaitForActiveSkillCasting";
}

EBTNodeResult::Type UTask_WaitForActiveSkill::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto casted_pawn = OwnerComp.GetAIOwner()->GetPawn();
	auto component = casted_pawn->GetComponentByClass(USkillContainer::StaticClass()); 
	if(auto casted_component = Cast<USkillContainer>(component))
	{
		WaitForMessage(OwnerComp, TEXT("CastingFinished"), casted_component->GetCastingRequestID());
		return EBTNodeResult::InProgress;
	}
	return EBTNodeResult::Failed;
}
