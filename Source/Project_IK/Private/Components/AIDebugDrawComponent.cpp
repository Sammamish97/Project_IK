/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 3.6.2025
Summary : Source file for AIDebugDrawComponent.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Components/AIDebugDrawComponent.h"

#include "AI/GunnerAIController.h"
#include "Characters/Unit.h"
#include "Components/CharacterStatComponent.h"
#include "Components/WeaponMechanics.h"

// Sets default values for this component's properties
UAIDebugDrawComponent::UAIDebugDrawComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAIDebugDrawComponent::SetActivated(bool activated)
{
	activated_ = activated;
	activated_time_ = -1.f;
	delta_time_ = 0.f;
}

void UAIDebugDrawComponent::SetActivated(float activated_time)
{
	activated_ = true;
	activated_time_ = activated_time;
	delta_time_ = 0.f;
}

// Called when the game starts
void UAIDebugDrawComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UAIDebugDrawComponent::InitAIController(AAIController* controller)
{
	//Pawn이 OnPossess되는 시점에 controller를 안전하게 얻을 수 있다.
	ai_controller_cache_ = Cast<AMeleeAIController>(controller);
	unit_cache_ = Cast<AUnit>(controller->GetCharacter());
	char_stat_cache_ = unit_cache_->GetComponentByClass<UCharacterStatComponent>();
	weapon_mechanics_cache_ = unit_cache_->GetComponentByClass<UWeaponMechanics>();
}

// Called every frame
void UAIDebugDrawComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (activated_)
	{
		if (ai_controller_cache_ != nullptr)
		{
			if (auto attack_target_actor = ai_controller_cache_->GetTargetActor())
			{
				if (activated_time_ >= 0.f)
				{
					if (activated_time_ < delta_time_)
					{
						SetActivated(false);
						return;
					}
					delta_time_ += DeltaTime;

					DrawDebugLine(GetWorld(), unit_cache_->GetActorLocation(), attack_target_actor->GetActorLocation(), FColor::Red, false, -1, 0, 3);
				}
				else
				{
					DrawDebugLine(GetWorld(), unit_cache_->GetActorLocation(), attack_target_actor->GetActorLocation(), FColor::Red, false, -1, 0, 3);
				}
			}
		}
	}
}
