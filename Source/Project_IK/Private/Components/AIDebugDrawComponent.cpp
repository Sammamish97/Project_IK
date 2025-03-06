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

	is_melee_ = false;
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

	//TODO: 현재 근거리/원거리의 분류를 weapon_mechanics의 보유 여부를 통해 확인한다. 더 좋은 방법이 있을 것이다.
	if (weapon_mechanics_cache_ == nullptr)
	{
		is_melee_ = true;
	}
}

// Called every frame
void UAIDebugDrawComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	//유닛 시야
	DrawDebugCircle(GetWorld(), unit_cache_->GetActorLocation(), char_stat_cache_->GetSightRange(), 32, FColor::Green,
		false, -1, 0, 0, {1, 0, 0}, {0, 1, 0}, false);

	if (ai_controller_cache_ != nullptr)
	{
		if (auto attack_target_actor = ai_controller_cache_->GetTargetActor())
		{
			DrawDebugLine(GetWorld(), unit_cache_->GetActorLocation(), attack_target_actor->GetActorLocation(), FColor::Red);
		}
		//원거리 유닛은 무기 사거리와 엄폐물 관련 debug draw역시 포함시킨다.
		if (is_melee_ == false)
		{
			//원거리 유닛이라면 사거리와 엄폐물 관련 Draw역시 포함시킨다.
			if (auto owned_cover = ai_controller_cache_->GetOwnedCover())
			{
				DrawDebugLine(GetWorld(), unit_cache_->GetActorLocation(), owned_cover->GetActorLocation(), FColor::Blue);
			}
		}
	}
}
