/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.06.2024
Summary : Source file for weapon magazine empty check decorator.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "AI/Decorator_IsPassiveAvailable.h"

#include "AIController.h"
#include "Abilities/PassiveMechanics.h"

UDecorator_IsPassiveAvailable::UDecorator_IsPassiveAvailable() 
{
	NodeName = TEXT("IsPassiveAvailable");
}

bool UDecorator_IsPassiveAvailable::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	//TODO: 현재 주기적으로 발동되는 패시브 기능은 오파츠로 넘어간 상태이다.
	auto casted_pawn = OwnerComp.GetAIOwner()->GetPawn();
	auto component = casted_pawn->GetComponentByClass(UPassiveMechanics::StaticClass()); 
	if(auto casted_component = Cast<UPassiveMechanics>(component))
	{
		return casted_component->IsPassiveAvailable();
	}
	UE_LOG(LogTemp, Error, TEXT("%s node can't find passive caster!"), *NodeName);
	return false;
}
