/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 02.27.2025
Summary : Header file for Map level player controller class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "WorldSettings/Map/IKMapController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "WorldSettings/Map/IKMapHUD.h"

class UEnhancedInputLocalPlayerSubsystem;

void AIKMapController::BeginPlay()
{
	Super::BeginPlay();
	if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		subsystem->AddMappingContext(player_input_mapping_context, 0);
	}}

void AIKMapController::SetupInputComponent()
{
	Super::SetupInputComponent();
	if (UEnhancedInputComponent* enhanced_input_component = Cast<UEnhancedInputComponent>(InputComponent))
	{
		enhanced_input_component->BindAction(inventory_toggle_action_, ETriggerEvent::Triggered, this, &AIKMapController::OnToggleInventory);
	}
}

void AIKMapController::ChangeLevel(FKey key)
{
	UE_LOG(LogTemp, Display, TEXT("Change Level"));
	UGameplayStatics::OpenLevel(GetWorld(), "DummyLevel");
}

void AIKMapController::OnToggleInventory()
{
	Cast<AIKMapHUD>(GetHUD())->ToggleInventory();
	Cast<AIKMapHUD>(GetHUD())->ToggleMap();
}
