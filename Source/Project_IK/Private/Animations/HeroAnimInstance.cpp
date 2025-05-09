/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.8.2025
Summary : Source file of Anim instance of Hero.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Animations/HeroAnimInstance.h"

#include "Characters/HeroBase.h"
#include "Components/WeaponMechanics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Managers/EnumCluster.h"

void UHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	hero_ptr_ = Cast<AHeroBase>(TryGetPawnOwner());
	if(auto hero = hero_ptr_.Get())
	{
		movement_component_ptr_ = hero->GetCharacterMovement();
	}
}

void UHeroAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if(anim_type_ == EWeaponAnimationType::INVALID)
	{
		if(auto hero = hero_ptr_.Get())
		{
			anim_type_ = hero->GetWeaponMechanics()->GetWeaponData().anim_type;
		}
	}
	
	if(auto movement_component = movement_component_ptr_.Get())
	{
		speed_ = movement_component->Velocity.Size2D();
	}
}