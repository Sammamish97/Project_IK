/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.29.2025
Summary : Source file for On Clear Cover Values Task.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "AI/Task_ClearCoverValues.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/Unit.h"
#include "Environments/Cover.h"

UTask_ClearCoverValues::UTask_ClearCoverValues()
{
	NodeName = "ClearCoverValues";
}

EBTNodeResult::Type UTask_ClearCoverValues::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	if (auto owned_cover = blackboard->GetValueAsObject(owned_cover_key_.SelectedKeyName))
	{
		blackboard->SetValueAsObject(owned_cover_key_.SelectedKeyName, nullptr);
		ACover* casted_cover = Cast<ACover>(owned_cover);
		casted_cover->SetCoveringOwner(nullptr);
		AUnit* casted_unit = Cast<AUnit>(OwnerComp.GetAIOwner()->GetPawn());
		casted_unit->DispatchUnitEvent(EUnitEvent::LeaveCover);
		casted_unit->SetCurHidingCover(nullptr);
	}
	return EBTNodeResult::Succeeded;
}
