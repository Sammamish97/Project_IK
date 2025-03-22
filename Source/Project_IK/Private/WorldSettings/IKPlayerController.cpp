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
#include "Kismet/GameplayStatics.h"
#include "WorldSettings/IKGameModeBase.h"
#include "Characters/HeroBase.h"
#include "WorldSettings/IKHUD.h"

AIKPlayerController::AIKPlayerController()
	: Super::APlayerController()
{
	targeting_component_ = CreateDefaultSubobject<UTargetingComponent>(TEXT("Targeting Component"));
}

void AIKPlayerController::BeginPlay()
{
	Super::BeginPlay();

	game_mode_cache_ = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));

	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;

	if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		subsystem->AddMappingContext(player_input_mapping_context, 0);
	}
}

void AIKPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* enhanced_input_component = Cast<UEnhancedInputComponent>(InputComponent))
	{
		// Deprecated code, but remain it for sake of later follwers.
		//enhanced_input_component->BindAction(toggle_map_action_, ETriggerEvent::Triggered, this, &AIKPlayerController::AFunctionYouWant);
		enhanced_input_component->BindAction(activate_first_hero_active_skill_action_, ETriggerEvent::Triggered, this, &AIKPlayerController::ActivateFirstHeroActiveSkill);
		enhanced_input_component->BindAction(activate_second_hero_active_skill_action, ETriggerEvent::Triggered, this, &AIKPlayerController::ActivateSecondHeroActiveSkill);
		enhanced_input_component->BindAction(activate_third_hero_active_skill_action, ETriggerEvent::Triggered, this, &AIKPlayerController::ActivateThirdHeroActiveSkill);
		enhanced_input_component->BindAction(activate_fourth_hero_active_skill_action, ETriggerEvent::Triggered, this, &AIKPlayerController::ActivateFourthHeroActiveSkill);
		enhanced_input_component->BindAction(enter_repositioning_mode_action_, ETriggerEvent::Triggered, this, &AIKPlayerController::EnterRepositioningMode);
		enhanced_input_component->BindAction(decide_action_, ETriggerEvent::Triggered, this, &AIKPlayerController::Decide);
		enhanced_input_component->BindAction(cancel_action_, ETriggerEvent::Triggered, this, &AIKPlayerController::CancelTargeting);

	}
}

UTargetingComponent* AIKPlayerController::GetTargetingComponent()
{
	return targeting_component_;
}

void AIKPlayerController::ActivateFirstHeroActiveSkill()
{
	UE_LOG(LogTemp, Display, TEXT("Select first hero"));
	selected_hero_idx_ = 0;
	ActivateSkill();
}

void AIKPlayerController::ActivateSecondHeroActiveSkill()
{
	UE_LOG(LogTemp, Display, TEXT("Select second hero"));
	selected_hero_idx_ = 1;
	ActivateSkill();
}

void AIKPlayerController::ActivateThirdHeroActiveSkill()
{
	UE_LOG(LogTemp, Display, TEXT("Select third hero"));
	selected_hero_idx_ = 2;
	ActivateSkill();
}

void AIKPlayerController::ActivateFourthHeroActiveSkill()
{
	UE_LOG(LogTemp, Display, TEXT("Select fourth hero"));
	selected_hero_idx_ = 3;
	ActivateSkill();
}

void AIKPlayerController::ActivateSkill()
{
	//IKTODO: selected_hero_idx에 대한 예외처리가 필요하다. int32대신 enum으로 접근하는게 더 올바를 수 도 있다.
	auto hero_array = game_mode_cache_->GetHeroContainers();
	auto cur_param = Cast<AHeroBase>(hero_array[selected_hero_idx_])->GetActiveSkillTargetParameters();
	if (cur_param.IsSet())
	{
		targeting_component_->StartSkillTargeting(hero_array[selected_hero_idx_], cur_param.GetValue());
		targeting_component_->SetTargetingState(ETargetingState::ActiveSKill);
	}
}


void AIKPlayerController::Decide()
{
	UE_LOG(LogTemp, Display, TEXT("Decide"));
	//targeting_component_->
	//여기서 스킬이 발동 되어야함!
}

void AIKPlayerController::CancelTargeting()
{
	targeting_component_->CancelTargeting();
}

void AIKPlayerController::EnterRepositioningMode()
{
	UE_LOG(LogTemp, Display, TEXT("EnterRepositioningMode"));
}

EPlayerState AIKPlayerController::GetPlayerState() const
{
	return player_state_;
}

void AIKPlayerController::SetPlayerState(EPlayerState new_state)
{
	player_state_ = new_state;
}
