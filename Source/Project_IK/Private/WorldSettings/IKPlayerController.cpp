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
		
		enhanced_input_component->BindAction(activate_first_item_action_, ETriggerEvent::Triggered, this, &AIKPlayerController::ActivateFirstItem);
		enhanced_input_component->BindAction(activate_second_item_action_, ETriggerEvent::Triggered, this, &AIKPlayerController::ActivateSecondItem);
		enhanced_input_component->BindAction(activate_third_item_action_, ETriggerEvent::Triggered, this, &AIKPlayerController::ActivateThirdItem);
	}
}

UTargetingComponent* AIKPlayerController::GetTargetingComponent()
{
	return targeting_component_;
}

void AIKPlayerController::ActivateFirstHeroActiveSkill()
{
	ActivateSkillTargeting(EHeroType::Hero1);
}

void AIKPlayerController::ActivateSecondHeroActiveSkill()
{
	ActivateSkillTargeting(EHeroType::Hero2);
}

void AIKPlayerController::ActivateThirdHeroActiveSkill()
{
	ActivateSkillTargeting(EHeroType::Hero3);
}

void AIKPlayerController::ActivateFourthHeroActiveSkill()
{
	ActivateSkillTargeting(EHeroType::Hero4);
}

void AIKPlayerController::ActivateSkillTargeting(EHeroType hero_type)
{
	targeting_component_->StartSkillTargeting(hero_type);
}

void AIKPlayerController::ActivateFirstItem()
{
	ActivateItemTargeting(0);
}

void AIKPlayerController::ActivateSecondItem()
{
	ActivateItemTargeting(1);
}

void AIKPlayerController::ActivateThirdItem()
{
	ActivateItemTargeting(2);
}

void AIKPlayerController::ActivateItemTargeting(int32 item_idx)
{
	targeting_component_->StartItemTargeting(item_idx);
}

void AIKPlayerController::Decide()
{
	UE_LOG(LogTemp, Display, TEXT("Decide"));
	targeting_component_->DecideAction();
}

void AIKPlayerController::CancelTargeting()
{
	targeting_component_->CancelTargeting();
}

void AIKPlayerController::EnterRepositioningMode()
{
	UE_LOG(LogTemp, Display, TEXT("EnterRepositioningMode"));
}