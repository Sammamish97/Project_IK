/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.29.2025
Summary : Source file for On Arrived Cover  Task.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "AI/Task_OnArrivedCover.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/Unit.h"
#include "Environments/Cover.h"
#include "Managers/EnumCluster.h"

UTask_OnArrivedCover::UTask_OnArrivedCover()
{
	NodeName = "On Arrived Cover";
}

EBTNodeResult::Type UTask_OnArrivedCover::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	if (auto owned_cover = blackboard->GetValueAsObject(owned_cover_key_.SelectedKeyName))
	{
		blackboard->SetValueAsEnum(unit_state_key_.SelectedKeyName, static_cast<uint8>(EUnitState::Attacking));
		AUnit* casted_unit = Cast<AUnit>(OwnerComp.GetAIOwner()->GetPawn());
		casted_unit->DispatchUnitEvent(EUnitEvent::HideOnCover);
		ACover* casted_cover = Cast<ACover>(owned_cover);
		casted_cover->SetCoveringOwner(casted_unit);
		casted_unit->SetCurHidingCover(casted_cover);
	}
	return EBTNodeResult::Succeeded;
}