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
#include "Weapons/Guns/GunBase.h"

UTask_BeginReload::UTask_BeginReload()
{
	NodeName = "BeginReload";
}

EBTNodeResult::Type UTask_BeginReload::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	auto casted_pawn = OwnerComp.GetAIOwner()->GetPawn();
	auto component = casted_pawn->GetComponentByClass(UWeaponMechanics::StaticClass());
	if(auto weapon_mechanics = Cast<UWeaponMechanics>(component))
	{
		weapon_mechanics->Reload();
		weapon_mechanics->GetWeaponActor()->OnFinishReload.AddDynamic(this, &UTask_BeginReload::OnFinishReload);
		return EBTNodeResult::InProgress;
	}
	return EBTNodeResult::Failed;
}

EBTNodeResult::Type UTask_BeginReload::AbortTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	FinishLatentAbort(OwnerComp);
	return Super::AbortTask(OwnerComp, NodeMemory);
}

void UTask_BeginReload::OnFinishReload(UBehaviorTreeComponent* bt_component, bool is_interrupted)
{
	auto casted_pawn = bt_component->GetAIOwner()->GetPawn();
	auto component = casted_pawn->GetComponentByClass(UWeaponMechanics::StaticClass());
	if(auto weapon_mechanics = Cast<UWeaponMechanics>(component))
	{
		weapon_mechanics->GetWeaponActor()->OnFinishReload.RemoveDynamic(this, &UTask_BeginReload::OnFinishReload);
		FinishLatentTask(*bt_component, is_interrupted ? EBTNodeResult::Failed : EBTNodeResult::Succeeded);
	}
}
