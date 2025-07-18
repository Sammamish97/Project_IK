/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 3.30.2025
Summary : Source file for Reset Gunner Value Task.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "AI/Task_ResetGunnerValues.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/Unit.h"
#include "Components/WeaponMechanics.h"
#include "Environments/Cover.h"
UTask_ResetGunnerValues::UTask_ResetGunnerValues()
{
	NodeName = "ResetGunnerValues";
}

EBTNodeResult::Type UTask_ResetGunnerValues::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	if (auto owned_cover = blackboard->GetValueAsObject(owned_cover_key_.SelectedKeyName))
	{
		blackboard->SetValueAsObject(owned_cover_key_.SelectedKeyName, nullptr);
		blackboard->SetValueAsBool(is_arrived_cover_key_.SelectedKeyName, false);

		ACover* casted_cover = Cast<ACover>(owned_cover);
		casted_cover->OnLeave();
		AUnit* casted_unit = Cast<AUnit>(OwnerComp.GetAIOwner()->GetPawn());
		casted_unit->DispatchUnitEvent(EUnitEvent::LeaveCover);
		casted_unit->SetCurHidingCover(nullptr);
	}

	TWeakObjectPtr<APawn> casted_pawn_ptr = OwnerComp.GetAIOwner()->GetPawn();
	if (auto casted_pawn = casted_pawn_ptr.Get())
	{
		if (auto weapon_mechanics = casted_pawn->GetComponentByClass<UWeaponMechanics>())
		{
			weapon_mechanics->FinishFire();
		}
	}
	return EBTNodeResult::Succeeded;
}
