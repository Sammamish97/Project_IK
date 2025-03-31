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

// Sets default values
AHeroAIController::AHeroAIController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	target_position_key_name_ = TEXT("TargetPosition");
}

void AHeroAIController::RepositionHero(FVector target_location)
{
	GetBlackboardComponent()->SetValueAsVector(target_position_key_name_, target_location);
	SetUnitState(EUnitState::Repositioning);
	DrawDebugSphere(GetWorld(), target_location, 32, 32, FColor::White, true, 1.0);
}

// Called when the game starts or when spawned
void AHeroAIController::BeginPlay()
{
	Super::BeginPlay();
	GetPathFollowingComponent()->OnRequestFinished.AddUObject(this, &AHeroAIController::OnArrivedTargetPosition);
}

void AHeroAIController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetPathFollowingComponent()->OnRequestFinished.RemoveAll(this);

	Super::EndPlay(EndPlayReason);
}

void AHeroAIController::OnArrivedTargetPosition(FAIRequestID request_id, const FPathFollowingResult& result)
{
	SetUnitState(EUnitState::Forwarding);
}

// Called every frame
void AHeroAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

