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
#include "Components/EnergySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Abilities/SupportSkills/SupportSkillBase.h"
#include "Characters/HeroBase.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/DataTableManager.h"
#include "WorldSettings/IKGameInstance.h"
#include "WorldSettings/IKGameModeBase.h"
#include "WorldSettings/IKHUD.h"
#include "WorldSettings/IKPlayerCameraManager.h"

AIKPlayerController::AIKPlayerController()
	: Super::APlayerController()
{
	targeting_component_ = CreateDefaultSubobject<UTargetingComponent>(TEXT("Targeting Component"));
	energy_system_component_ = CreateDefaultSubobject<UEnergySystemComponent>(TEXT("Energy System Component"));
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
	
	auto type =Cast<UIKGameInstance>(GetGameInstance())->GetDataTableManager()->GetSupportSkillType(ESupportSkillType::Reposition);
	equipped_support_skills_.Push(NewObject<USupportSkillBase>(this, type));
}

void AIKPlayerController::Tick(float dt)
{
	Super::Tick(dt);
}

void AIKPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	on_support_skill_.Clear();
	on_active_skill_.Clear();
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

void AIKPlayerController::ActivateFirstSupportSkill()
{
	if (equipped_support_skills_[0])
	{
		ActivateSupportSkill(0);
	}
}

void AIKPlayerController::ActivateSecondSupportSkill()
{
	if (equipped_support_skills_[1])
	{
		ActivateSupportSkill(1);
	}
}

void AIKPlayerController::ActivateThirdSupportSkill()
{
	if (equipped_support_skills_[2])
	{
		ActivateSupportSkill(2);
	}
}

void AIKPlayerController::ActivateSkillTargeting(EHeroType hero_type)
{
	auto game_mode_cache = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (auto selected_hero = game_mode_cache->GetHero(hero_type))
	{
		AHeroBase* casted_hero = Cast<AHeroBase>(selected_hero);
		if (casted_hero->HasActiveSkill())
		{
			if (casted_hero->IsActiveSkillOnCoolDown() == false)
			{
				selected_hero_type_ = hero_type;
				StartTargeting(casted_hero->GetActiveSkillTargetParameters().GetValue(), ETargetingState::ActiveSKill, casted_hero);
			}
		}
	}
}

void AIKPlayerController::ActivateSupportSkill(int32 support_num)
{
	if (energy_system_component_->GetEnergy() >  equipped_support_skills_[support_num]->GetCost())
	{
		last_invoked_support_skill_ = equipped_support_skills_[support_num];
		last_invoked_support_skill_->ActivateSkill();
	}
}

void AIKPlayerController::StartTargeting(const FTargetParameters& target_params, ETargetingState state, AActor* invoker)
{
	if (cur_targeting_state_ == ETargetingState::Idle)
	{
		targeting_component_->StartTargeting(target_params, invoker);
		cur_targeting_state_ = state;
	}
}

void AIKPlayerController::ClearTargetingState()
{
	cur_targeting_state_ = ETargetingState::Idle;
}

bool AIKPlayerController::UseEnergy(float amount)
{
	return energy_system_component_->UseEnergy(amount);
}

void AIKPlayerController::Decide()
{
	switch (cur_targeting_state_)
	{
		case ETargetingState::ActiveSKill:
			{
				auto game_mode_cache = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
				auto target_result = targeting_component_->DecideTargetings();
				Cast<AHeroBase>(game_mode_cache->GetHero(selected_hero_type_))->InvokeActiveSkill(target_result);
				on_active_skill_.Broadcast(selected_hero_type_);
				ClearTargetingState();
			}
			break;
		case ETargetingState::SupportSkill:
			{
				last_invoked_support_skill_->Decide(targeting_component_->DecideTargetings());
				on_support_skill_.Broadcast(0);
			}
			break;
	}
	
}

void AIKPlayerController::CancelTargeting()
{
	targeting_component_->CancelTargeting();
	ClearTargetingState();
	if (last_invoked_support_skill_)
	{
		last_invoked_support_skill_->Reset();
	}
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