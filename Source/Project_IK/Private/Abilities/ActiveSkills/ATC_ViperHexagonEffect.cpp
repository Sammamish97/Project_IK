/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 04.22.2025
Summary : Source file for viper hexagon Effect Component.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Abilities/ActiveSkills/ATC_ViperHexagonEffect.h"

#include "Characters/Unit.h"
#include "Managers/EnumCluster.h"

// Sets default values for this component's properties
UATC_ViperHexagonEffect::UATC_ViperHexagonEffect()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UATC_ViperHexagonEffect::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UATC_ViperHexagonEffect::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearTimer(duration_timer_handle_);
	Super::EndPlay(EndPlayReason);
}

// Called every frame
void UATC_ViperHexagonEffect::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UATC_ViperHexagonEffect::IncreaseStack()
{
	AUnit* unit = Cast<AUnit>(GetOwner());
	if (unit)
	{

		GetWorld()->GetTimerManager().ClearTimer(duration_timer_handle_);
		FTimerDelegate expired_delegate = FTimerDelegate::CreateUObject(this, &UATC_ViperHexagonEffect::OnDurationExpired);
		GetWorld()->GetTimerManager().SetTimer(duration_timer_handle_, expired_delegate, effect_duration_, false);

		unit->ApplyCrowdControl(ECCType::Bleeding, effect_duration_);
		stack_ += 1;
		if (stack_ >= max_stack_)
		{
			OnMaxStack();
		}
	}
}

void UATC_ViperHexagonEffect::OnMaxStack()
{
	TWeakObjectPtr<AActor> owner = GetOwner();
	if (AActor* owner_ptr = owner.Get())
	{
		AUnit* unit_ptr = Cast<AUnit>(owner_ptr);
		unit_ptr->GetDamage({33, 0, EDamageType::Projectile});
	}
	DestroyComponent();
}

void UATC_ViperHexagonEffect::OnDurationExpired()
{
	DestroyComponent();
}
