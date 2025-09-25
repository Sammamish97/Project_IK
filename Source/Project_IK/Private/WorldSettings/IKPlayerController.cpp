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
#include "Characters/HeroBase.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/PauseManager.h"
#include "WorldSettings/IKGameState.h"
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
	bShouldPerformFullTickWhenPaused = true;
	
	game_state_cache_ = Cast<AIKGameState>(UGameplayStatics::GetGameState(GetWorld()));
	pause_manager_ = NewObject<UPauseManager>(this, pause_manager_class_);
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
		
		enhanced_input_component->BindAction(toggle_focus_mode_action_, ETriggerEvent::Triggered, this, &AIKPlayerController::ToggleFocusMode);
		enhanced_input_component->BindAction(toggle_pause_action_, ETriggerEvent::Triggered, this, &AIKPlayerController::TogglePause);
	}
}

UTargetingComponent* AIKPlayerController::GetTargetingComponent()
{
	return targeting_component_;
}

void AIKPlayerController::AddEnemyToCameraManager(AActor* tracked_enemy)
{
	AIKPlayerCameraManager * camera_manger = Cast<AIKPlayerCameraManager>(PlayerCameraManager);

	camera_manger->AddEnemy(tracked_enemy);
}

void AIKPlayerController::ActivateFirstHeroActiveSkill()
{
	game_state_cache_->ActivateSkillTargeting(EHeroType::Hero1);
}

void AIKPlayerController::ActivateSecondHeroActiveSkill()
{
	game_state_cache_->ActivateSkillTargeting(EHeroType::Hero2);
}

void AIKPlayerController::ActivateThirdHeroActiveSkill()
{
	game_state_cache_->ActivateSkillTargeting(EHeroType::Hero3);
}

void AIKPlayerController::ActivateFourthHeroActiveSkill()
{
	game_state_cache_->ActivateSkillTargeting(EHeroType::Hero4);
}

void AIKPlayerController::ActivateFirstSupportSkill()
{
	game_state_cache_->ActivateSupportSkill(ESupportSkillType::SetAttackTarget);
}

void AIKPlayerController::ActivateSecondSupportSkill()
{
	game_state_cache_->ActivateSupportSkill(ESupportSkillType::Reposition);
}

void AIKPlayerController::ActivateThirdSupportSkill()
{
	game_state_cache_->ActivateSupportSkill(ESupportSkillType::Maintain);
}

void AIKPlayerController::StartTargeting(const FTargetParameters& target_params, AActor* invoker)
{
	targeting_component_->StartTargeting(target_params, invoker);
}

void AIKPlayerController::FinishTargeting()
{
}

void AIKPlayerController::Decide()
{
	game_state_cache_->OnDecide(targeting_component_->DecideTargetings());
}

void AIKPlayerController::CancelTargeting()
{
	targeting_component_->CancelTargeting();
	game_state_cache_->ClearTargetingState();
	FinishTargeting();
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

void AIKPlayerController::ToggleFocusMode()
{
	game_state_cache_->ToggleFocusMode();
}

void AIKPlayerController::TogglePause()
{
	on_pause_ = !on_pause_;
	pause_manager_->TogglePause(on_pause_);
	SetPause(on_pause_);
}
