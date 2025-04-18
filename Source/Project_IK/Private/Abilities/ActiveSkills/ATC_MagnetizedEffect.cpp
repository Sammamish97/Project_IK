/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 04.18.2025
Summary : Source file for Magnetized Effect Component.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/ActiveSkills/ATC_MagnetizedEffect.h"

#include "Characters/Unit.h"

// Sets default values for this component's properties
UATC_MagnetizedEffect::UATC_MagnetizedEffect()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UATC_MagnetizedEffect::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UATC_MagnetizedEffect::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearTimer(duration_timer_handle_);
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void UATC_MagnetizedEffect::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FTimerDelegate expired_delegate = FTimerDelegate::CreateUObject(this, &UATC_MagnetizedEffect::OnDurationExpired);
	GetWorld()->GetTimerManager().SetTimer(duration_timer_handle_, expired_delegate, duration_, false);
}

void UATC_MagnetizedEffect::IncreaseStack()
{
	GetWorld()->GetTimerManager().ClearTimer(duration_timer_handle_);
	FTimerDelegate expired_delegate = FTimerDelegate::CreateUObject(this, &UATC_MagnetizedEffect::OnDurationExpired);
	GetWorld()->GetTimerManager().SetTimer(duration_timer_handle_, expired_delegate, duration_, false);
	
	stack_ += 1;
	if (stack_ >= max_stack_)
	{
		OnMaxStack();
	}
}

void UATC_MagnetizedEffect::OnMaxStack()
{
	TWeakObjectPtr<AActor> owner = GetOwner();
	if (AActor* owner_ptr = owner.Get())
	{
		Cast<AUnit>(owner_ptr)->GetDamage({33, 0, EDamageType::Projectile});
	}
	DestroyComponent();
}

void UATC_MagnetizedEffect::OnDurationExpired()
{
	DestroyComponent();
}

