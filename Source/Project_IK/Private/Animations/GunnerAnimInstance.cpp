/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 5.8.2025
Summary : Source file of Anim instance of Hero.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Animations/GunnerAnimInstance.h"

#include "Characters/HeroBase.h"
#include "Components/WeaponMechanics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Managers/EnumCluster.h"

void UGunnerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	gunner_ptr_ = Cast<AUnit>(TryGetPawnOwner());
	if(auto hero = gunner_ptr_.Get())
	{
		movement_component_ptr_ = hero->GetCharacterMovement();
	}
}

void UGunnerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if(anim_type_ == EWeaponAnimationType::INVALID)
	{
		if(auto gunner = gunner_ptr_.Get())
		{
			if(auto weapon_mechanics = gunner->GetComponentByClass<UWeaponMechanics>())
			{
				anim_type_ = weapon_mechanics->GetWeaponData().anim_type;
			}
		}
	}
	
	if(auto movement_component = movement_component_ptr_.Get())
	{
		speed_ = movement_component->Velocity.Size2D();
	}
	
	if(auto gunner = gunner_ptr_.Get())
	{
		pitch_ = gunner->GetPitchDiffBetweenTarget();
		if (pitch_ > 180.f)
		{
			pitch_ = 360.f - pitch_;
		}
	}
}