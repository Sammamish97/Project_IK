/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.06.2024
Summary : Source file for Aimmed check decorator.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "AI/Decorator_IsAimmed.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UDecorator_IsAimmed::UDecorator_IsAimmed()
{
	NodeName = "IsAimmed";
}

bool UDecorator_IsAimmed::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UBlackboardComponent* blackboard = OwnerComp.GetBlackboardComponent();
	AAIController* controller = OwnerComp.GetAIOwner();
	APawn* casted_pawn = controller->GetPawn();
	casted_pawn->GetBaseAimRotation();
	AActor* attack_target = Cast<AActor>(blackboard->GetValueAsObject(attack_target_key_.SelectedKeyName));

	if(attack_target)
	{
		//이동사격이 가능하지 않는 한, 조준 시에는 반드시 MoveTo가 멈춰야 한다.
		controller->StopMovement();
		FVector owner_to_target = attack_target->GetActorLocation() - casted_pawn->GetActorLocation();
		owner_to_target.Normalize();
		FVector owner_forward = casted_pawn->GetActorForwardVector();
		owner_forward.Normalize();
		
		return FVector::DotProduct({owner_to_target.X, owner_to_target.Y, 0}, {owner_forward.X, owner_forward.Y, 0})  >= 0.8;
	}
	return false;
}
