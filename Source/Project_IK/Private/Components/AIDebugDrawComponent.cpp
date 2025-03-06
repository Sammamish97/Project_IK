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
	unit_cache_ = Cast<AUnit>(GetOwner());
	
	char_stat_cache_ = unit_cache_->GetComponentByClass<UCharacterStatComponent>();
	weapon_mechanics_cache_ = unit_cache_->GetComponentByClass<UWeaponMechanics>();
	ai_controller_cache_ = Cast<AGunnerAIController>(unit_cache_->GetController());

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

	if (is_melee_ == false)
	{
		//원거리 유닛이라면 사거리와 엄폐물 관련 Draw역시 포함시킨다.
		
	}
	DrawDebugCircle(GetWorld(), unit_cache_->GetActorLocation(), char_stat_cache_->GetSightRange(), 32, FColor::Red);
}

