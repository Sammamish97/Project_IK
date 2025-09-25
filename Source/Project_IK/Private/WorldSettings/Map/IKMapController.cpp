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
#include "Managers/InventoryManager.h"

#include "Managers/PauseManager.h"
#include "WorldSettings/IKGameInstance.h"

void AIKMapController::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = true;
	bShouldPerformFullTickWhenPaused = true;
	
	if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		subsystem->AddMappingContext(player_input_mapping_context, 0);
	}

	pause_manager_ = NewObject<UPauseManager>(this, pause_manager_class_);
}

void AIKMapController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* enhanced_input_component = Cast<UEnhancedInputComponent>(InputComponent))
	{
		enhanced_input_component->BindAction(toggle_pause_action_, ETriggerEvent::Triggered, this, &AIKMapController::TogglePause);
		enhanced_input_component->BindAction(toggle_inventory_action_, ETriggerEvent::Triggered, this, &AIKMapController::ToggleInventory);
	}
}

void AIKMapController::TogglePause()
{
	on_pause_ = !on_pause_;
	if (pause_manager_)
	{
		pause_manager_->TogglePause(on_pause_);
	}
	SetPause(on_pause_);
}

void AIKMapController::ToggleInventory()
{
	UIKGameInstance* game_instance = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (auto inventory_manager_ = game_instance->GetInventoryManager())
	{
		inventory_manager_->ToggleReadOnlyInventoryWidget();
	}
}
