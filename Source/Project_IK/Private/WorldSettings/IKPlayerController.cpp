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

void AIKPlayerController::Tick(float dt)
{
	Super::Tick(dt);
	if (cur_charge_time_ <= reposition_stack_)
	{
		cur_charge_time_ += dt;
		cur_charge_time_ = FMath::Clamp(cur_charge_time_, 0.f, reposition_stack_);
	}
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
				targeting_state_ = ETargetingState::Idle;
			}
			break;
		case ETargetingState::Item:
			{
				auto item_inventory = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GetItemInventory();
				//IKTODO: Item의 사용 가능 유무를 확인 후 발동해야 함!
				item_inventory->UseItem(selected_item_idx_, target_result);
				on_item_used_.Broadcast(selected_item_idx_);
				targeting_state_ = ETargetingState::Idle;
			}
			break;
		case ETargetingState::EnterRepositioning:
			{
				UE_LOG(LogTemp, Display, TEXT("AIKPlayerController::EnterRepositioning"));
				if (target_result.target_actors_.IsEmpty() == false)
				{
					//IKTODO: 영웅의 선택과 이동명령 사이 영웅이 죽을 수 있다. WeakPtr이 좋을지도...?
					targeting_component_->SetTargetParams({ETargetingMode::Location, ETargetType::None, 1000, 1000});
					repositioning_hero_ = target_result.target_actors_[0];
					targeting_state_ = ETargetingState::PickRepositionTargetLocation;
				}
			}
			break;
		case ETargetingState::PickRepositionTargetLocation:
			{
				UE_LOG(LogTemp, Display, TEXT("AIKPlayerController::PickRepositionTargetLocation"));
				if (cur_charge_time_ > 1.f && repositioning_hero_ != nullptr)
				{
					cur_charge_time_ -= 1.f;
					Cast<AHeroBase>(repositioning_hero_)->Reposition(target_result.target_location_);
					targeting_state_ = ETargetingState::Idle;
					repositioning_hero_ = nullptr;
				}
			}
			break;
			case ETargetingState::Idle:
			default:
				break;
	}
}

void AIKPlayerController::CancelTargeting()
{
	targeting_component_->CancelTargeting();
}

void AIKPlayerController::EnterRepositioningMode()
{
	float HARD_CODED_RADIUS = 1000;
	targeting_state_ = ETargetingState::EnterRepositioning;
	targeting_component_->StartTargeting( {ETargetingMode::Actor, ETargetType::Allies, HARD_CODED_RADIUS, HARD_CODED_RADIUS}, nullptr);
}

void AIKPlayerController::RotateCameraLeft()
{
	//IKTODO: 카메라 좌회전 로직.
}

void AIKPlayerController::RotateCameraRight()
{
	//IKTODO: 카메라 우회전 로직.
}

int32 AIKPlayerController::GetRepositionStack() const
{
	return reposition_stack_;
}

float AIKPlayerController::GetChargeTime() const
{
	return cur_charge_time_;
}
