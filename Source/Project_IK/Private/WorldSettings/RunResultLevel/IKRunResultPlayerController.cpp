/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 04.02.2025
Summary : Source file for Player Controller in RunResult level.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "WorldSettings/RunResultLevel/IKRunResultPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

#include "WorldSettings/RunResultLevel/IKRunResultHUD.h"

void AIKRunResultPlayerController::BeginPlay()
{
	Super::BeginPlay();

    // Enable the mouse cursor
    bShowMouseCursor = true;
    SetInputMode(FInputModeGameAndUI());

    if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        subsystem->AddMappingContext(player_input_mapping_context, 0);
    }
}

void AIKRunResultPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

    if (UEnhancedInputComponent* enhanced_input_component = Cast<UEnhancedInputComponent>(InputComponent))
    {
        enhanced_input_component->BindAction(decide_action_, ETriggerEvent::Triggered, this, &AIKRunResultPlayerController::KeyboardAction, decide_action_.Get());
        enhanced_input_component->BindAction(enter_repositioning_mode_action_, ETriggerEvent::Triggered, this, &AIKRunResultPlayerController::KeyboardAction, enter_repositioning_mode_action_.Get());
    }
}

void AIKRunResultPlayerController::KeyboardAction(UInputAction* input_action)
{
    if (AIKRunResultHUD* hud = Cast<AIKRunResultHUD>(GetHUD()))
    {
        FKey confirm_key = GetKeyFromInputAction(input_action);
        hud->HandleKeyboardAction(FKeyEvent(confirm_key, FModifierKeysState(), 0, false, 0, 0));
    }
}

FKey AIKRunResultPlayerController::GetKeyFromInputAction(UInputAction* input_action)
{
    if (player_input_mapping_context)
    {
        const TArray<FEnhancedActionKeyMapping>& mappings = player_input_mapping_context->GetMappings();

        for (const FEnhancedActionKeyMapping& mapping : mappings)
        {
            if (mapping.Action == input_action)
            {
                return mapping.Key;
            }
        }
    }
    check("Given input action is not Valid!!");
    return FKey();
}
