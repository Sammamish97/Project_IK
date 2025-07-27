/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.03.2024
Summary : Source file for Gunner AI Controller.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "AI/GunnerAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

AGunnerAIController::AGunnerAIController()
{
	owned_cover_key_name_ = TEXT("OwnedCover");
	fire_state_key_name_ = TEXT("FireState");
	reload_state_key_name_ = TEXT("ReloadState");
}

void AGunnerAIController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

AActor* AGunnerAIController::GetOwnedCover()
{
	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(owned_cover_key_name_));
}
