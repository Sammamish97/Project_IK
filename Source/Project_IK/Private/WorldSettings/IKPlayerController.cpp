/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 10.04.2024
Summary : Source file for Player Controller.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "WorldSettings/IKPlayerController.h"

#include "Components/TargetingComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Abilities/SupportSkills/SupportSkillBase.h"
#include "Characters/HeroBase.h"
#include "Kismet/GameplayStatics.h"
#include "WorldSettings/IKGameModeBase.h"
#include "WorldSettings/IKGameState.h"
#include "WorldSettings/IKHUD.h"
#include "WorldSettings/IKPlayerCameraManager.h"

AIKPlayerController::AIKPlayerController()
	: Super::APlayerController()
{
	targeting_component_ = CreateDefaultSubobject<UTargetingComponent>(TEXT("Targeting Component"));
}

void AIKPlayerController::BeginPlay()
{
	Super::BeginPlay();
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;

	game_state_cache_ = Cast<AIKGameState>(UGameplayStatics::GetGameState(GetWorld()));

	if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		subsystem->AddMappingContext(player_input_mapping_context, 0);
	}
}

void AIKPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AIKPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* enhanced_input_component = Cast<UEnhancedInputComponent>(InputComponent))
	{
		enhanced_input_component->BindAction(activate_first_hero_active_skill_action_, ETriggerEvent::Triggered, this, &AIKPlayerController::ActivateFirstHeroActiveSkill);
		enhanced_input_component->BindAction(activate_second_hero_active_skill_action, ETriggerEvent::Triggered, this, &AIKPlayerController::ActivateSecondHeroActiveSkill);
		enhanced_input_component->BindAction(activate_third_hero_active_skill_action, ETriggerEvent::Triggered, this, &AIKPlayerController::ActivateThirdHeroActiveSkill);
		enhanced_input_component->BindAction(activate_fourth_hero_active_skill_action, ETriggerEvent::Triggered, this, &AIKPlayerController::ActivateFourthHeroActiveSkill);

		enhanced_input_component->BindAction(activate_first_support_skill_action_, ETriggerEvent::Triggered, this, &AIKPlayerController::ActivateFirstSupportSkill);
		enhanced_input_component->BindAction(activate_second_support_skill_action, ETriggerEvent::Triggered, this, &AIKPlayerController::ActivateSecondSupportSkill);
		enhanced_input_component->BindAction(activate_third_support_skill_action, ETriggerEvent::Triggered, this, &AIKPlayerController::ActivateThirdSupportSkill);
		
		enhanced_input_component->BindAction(decide_action_, ETriggerEvent::Triggered, this, &AIKPlayerController::Decide);
		enhanced_input_component->BindAction(cancel_action_, ETriggerEvent::Triggered, this, &AIKPlayerController::CancelTargeting);
		
		enhanced_input_component->BindAction(rotate_camera_left_action_, ETriggerEvent::Triggered, this, &AIKPlayerController::RotateCameraLeft);
		enhanced_input_component->BindAction(rotate_camera_right_action_, ETriggerEvent::Triggered, this, &AIKPlayerController::RotateCameraRight);

		enhanced_input_component->BindAction(inventory_toggle_action_, ETriggerEvent::Triggered, this, &AIKPlayerController::OnToggleInventory);
	}
}

UTargetingComponent* AIKPlayerController::GetTargetingComponent()
{
	return targeting_component_;
}

void AIKPlayerController::UpdateEnemies(TArray<TWeakObjectPtr<AActor>> tracked_enemies)
{
	AIKPlayerCameraManager * camera_manger = Cast<AIKPlayerCameraManager>(PlayerCameraManager);

	camera_manger->UpdateEnemies(tracked_enemies);
}

void AIKPlayerController::ActivateFirstHeroActiveSkill()
{
	game_state_cache_->ActivateActiveSkill(EHeroType::Hero1);
}

void AIKPlayerController::ActivateSecondHeroActiveSkill()
{
	game_state_cache_->ActivateActiveSkill(EHeroType::Hero2);
}

void AIKPlayerController::ActivateThirdHeroActiveSkill()
{
	game_state_cache_->ActivateActiveSkill(EHeroType::Hero3);
}

void AIKPlayerController::ActivateFourthHeroActiveSkill()
{
	game_state_cache_->ActivateActiveSkill(EHeroType::Hero4);
}

void AIKPlayerController::ActivateFirstSupportSkill()
{
	game_state_cache_->ActivateSupportSkill(0);
}

void AIKPlayerController::ActivateSecondSupportSkill()
{
	game_state_cache_->ActivateSupportSkill(1);
}

void AIKPlayerController::ActivateThirdSupportSkill()
{
	game_state_cache_->ActivateSupportSkill(2);
}

void AIKPlayerController::StartTargeting(const FTargetParameters& target_params, AActor* invoker)
{
	if (cur_targeting_state_ == ETargetingState::Idle)
	{
		targeting_component_->StartTargeting(target_params, invoker);
		cur_targeting_state_ = ETargetingState::OnTargeting;
	}
}

void AIKPlayerController::ClearTargetingState()
{
	cur_targeting_state_ = ETargetingState::Idle;
}

void AIKPlayerController::Decide()
{
	game_state_cache_->DecideLastInvokedSkill(targeting_component_->DecideTargetings());
}

void AIKPlayerController::CancelTargeting()
{
	targeting_component_->CancelTargeting();
	game_state_cache_->ClearLastInvokedSkill();
	ClearTargetingState();
}

void AIKPlayerController::RotateCameraLeft()
{
	AIKPlayerCameraManager* camera_manger = Cast<AIKPlayerCameraManager>(PlayerCameraManager);
	camera_manger->RotateCameraLeft();
}

void AIKPlayerController::RotateCameraRight()
{
	AIKPlayerCameraManager* camera_manger = Cast<AIKPlayerCameraManager>(PlayerCameraManager);
	camera_manger->RotateCameraRight();
}

void AIKPlayerController::OnToggleInventory()
{
	Cast<AIKHUD>(GetHUD())->ToggleInventory();
}