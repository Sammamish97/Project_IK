/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 3.29.2025
Summary : Source file for Hero AI Controller.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "AI/HeroAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/HeroBase.h"

// Sets default values
AHeroAIController::AHeroAIController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	relocate_target_position_key_name_ = TEXT("TargetPosition");
}

void AHeroAIController::RepositionHero(FVector target_location)
{
	SetFocus(nullptr);
	ClearFocus(EAIFocusPriority::Default);
	GetBlackboardComponent()->SetValueAsVector(relocate_target_position_key_name_, target_location);
}

void AHeroAIController::SetAttackTarget(AActor* target)
{
	GetBlackboardComponent()->SetValueAsObject(attack_target_key_name_, target);
}

void AHeroAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);
	Cast<AHeroBase>(GetPawn())->ResetUnitState();
}

// Called when the game starts or when spawned
void AHeroAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AHeroAIController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetPathFollowingComponent()->OnRequestFinished.RemoveAll(this);

	Super::EndPlay(EndPlayReason);
}

// Called every frame
void AHeroAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

