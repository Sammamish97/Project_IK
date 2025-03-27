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
#include "Abilities/Item.h"
#include "Abilities/ItemInventory.h"
#include "Characters/HeroBase.h"
#include "Kismet/GameplayStatics.h"
#include "WorldSettings/IKGameInstance.h"
#include "WorldSettings/IKGameModeBase.h"

class AHeroBase;

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

	if (UEnhancedInputLocalPlayerSubsystem* subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		subsystem->AddMappingContext(player_input_mapping_context, 0);
	}
}

void AIKPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	on_item_used_.Clear();
	on_active_skill_.Clear();
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

		enhanced_input_component->BindAction(rotate_camera_left_action_, ETriggerEvent::Triggered, this, &AIKPlayerController::RotateCameraLeft);
		enhanced_input_component->BindAction(rotate_camera_right_action_, ETriggerEvent::Triggered, this, &AIKPlayerController::RotateCameraRight);
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
				targeting_state_ = ETargetingState::ActiveSKill;
				targeting_component_->StartTargeting(casted_hero->GetActiveSkillTargetParameters().GetValue(), casted_hero);
			}
		}
	}
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
	auto item_inventory = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GetItemInventory();
	auto cur_item = item_inventory->GetItem(item_idx);
	if (cur_item == nullptr)
	{
		return;
	}
	selected_item_idx_ = item_idx;
	targeting_state_ = ETargetingState::Item;
	targeting_component_->StartTargeting(cur_item->GetTargetParameters());
}

void AIKPlayerController::Decide()
{
	auto game_mode_cache = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	auto target_result = targeting_component_->DecideTargetings();
	
	switch (targeting_state_)
	{
		case ETargetingState::ActiveSKill:
			{
				Cast<AHeroBase>(game_mode_cache->GetHero(selected_hero_type_))->InvokeActiveSkill(target_result);
				on_active_skill_.Broadcast(selected_hero_type_);
			}
			break;
		case ETargetingState::Item:
			{
				auto item_inventory = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GetItemInventory();
				//IKTODO: Item의 사용 가능 유무를 확인 후 발동해야 함!
				item_inventory->UseItem(selected_item_idx_, target_result);
				on_item_used_.Broadcast(selected_item_idx_);
			}
			break;

		case ETargetingState::RePositioning:
			{
				Cast<AHeroBase>(game_mode_cache->GetHero(selected_hero_type_))->Reposition(target_result);
			}
			break;
			case ETargetingState::Idle:
			default:
				break;
	}
	targeting_state_ = ETargetingState::Idle;
}

void AIKPlayerController::CancelTargeting()
{
	targeting_component_->CancelTargeting();
}

void AIKPlayerController::EnterRepositioningMode()
{
	//targeting_component_->StartTargeting(hero_type);
}

void AIKPlayerController::RotateCameraLeft()
{
	//IKTODO: 카메라 좌회전 로직.
}

void AIKPlayerController::RotateCameraRight()
{
	//IKTODO: 카메라 우회전 로직.
}
