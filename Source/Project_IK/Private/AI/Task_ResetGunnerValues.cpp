/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 3.30.2025
Summary : Source file for Reset Gunner Value Task.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "AI/Task_ResetGunnerValues.h"
#include "BehaviorTree/BlackboardComponent.h"
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
		Cast<ACover>(owned_cover)->SetCoveringOwner(nullptr);
		blackboard->SetValueAsObject(owned_cover_key_.SelectedKeyName, nullptr);
		blackboard->SetValueAsObject(attack_target_key_.SelectedKeyName, nullptr);
		
	}
	return EBTNodeResult::Succeeded;
}
