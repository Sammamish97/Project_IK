/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.17.2024
Summary : Source file for Begin Reload Task.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "AI/Task_BeginReload.h"

#include "AIController.h"
#include "Components/WeaponMechanics.h"

UTask_BeginReload::UTask_BeginReload()
{
	NodeName = "BeginReload";
}

EBTNodeResult::Type UTask_BeginReload::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto casted_pawn = OwnerComp.GetAIOwner()->GetPawn();
	auto component = casted_pawn->GetComponentByClass(UWeaponMechanics::StaticClass()); 
	if(auto casted_component = Cast<UWeaponMechanics>(component))
	{
		casted_component->Reload();
		WaitForMessage(OwnerComp, TEXT("ReloadFinished"), casted_component->GetReloadRequestId());
		return EBTNodeResult::InProgress;
	}
	return EBTNodeResult::Failed;
}
