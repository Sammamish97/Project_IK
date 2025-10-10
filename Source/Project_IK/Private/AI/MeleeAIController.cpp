/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 12.08.2024
Summary : Source file for Melee AI Controller.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "AI/MeleeAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/AIDebugDrawComponent.h"

AMeleeAIController::AMeleeAIController()
{
	debug_draw_component_ = CreateDefaultSubobject<UAIDebugDrawComponent>(TEXT("DebugDrawComponent"));
	
	target_class_key_name_ = TEXT("TargetClass");
	unit_state_key_name_ = TEXT("UnitState");
	stun_state_key_name_ = TEXT("StunState");
	attack_target_key_name_ = TEXT("AttackTarget");
	ai_find_target_key_name_ = TEXT("FindTarget");
}

void AMeleeAIController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearTimer(timer_handle_);
	Super::EndPlay(EndPlayReason);
}

void AMeleeAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if(behavior_tree_)
	{
		RunBehaviorTree(behavior_tree_);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("BlackBoard isn't exist!"));
	}
	if(GetBlackboardComponent()->IsValidKey(GetBlackboardComponent()->GetKeyID(target_class_key_name_)))
	{
		GetBlackboardComponent()->SetValueAsClass(target_class_key_name_, target_class_);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Target class key name is wrong!"));
	}
	if(GetBlackboardComponent()->IsValidKey(GetBlackboardComponent()->GetKeyID(unit_state_key_name_)))
	{
		GetBlackboardComponent()->SetValueAsEnum(unit_state_key_name_, static_cast<uint8>(EUnitState::OnLogic));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("unit state enum key name is wrong!"));
	}
	debug_draw_component_->InitAIController(this);
}

void AMeleeAIController::GetStunned()
{
	SetUnitState(EUnitState::OnStunned);
}

void AMeleeAIController::FinishStun()
{
}

AActor* AMeleeAIController::GetOwnedCover()
{
	//근접 유닛은 엄폐하지 않는다.
	return nullptr;
}

AActor* AMeleeAIController::GetTargetActor()
{
	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(attack_target_key_name_));
}

void AMeleeAIController::SetTargetActor(AActor* target_actor)
{
	GetBlackboardComponent()->SetValueAsObject(attack_target_key_name_, target_actor);
}

void AMeleeAIController::SetUnitState(EUnitState new_state)
{
	GetBlackboardComponent()->SetValueAsEnum(unit_state_key_name_, static_cast<uint8>(new_state));
}

void AMeleeAIController::SetDebugDrawActivated(bool activated)
{
	debug_draw_component_->SetActivated(activated);
}

void AMeleeAIController::SetDebugDrawActivated(float activated)
{
	debug_draw_component_->SetActivated(activated);
}

void AMeleeAIController::SetAIFindTargetType(EAIFindTargetType type)
{
	GetBlackboardComponent()->SetValueAsEnum(ai_find_target_key_name_, static_cast<uint8>(type));
}

void AMeleeAIController::ResetUnitState()
{
	SetUnitState(EUnitState::OnLogic);
}
