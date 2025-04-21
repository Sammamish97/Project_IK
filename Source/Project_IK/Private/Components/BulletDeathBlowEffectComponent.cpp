/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.21.2025
Summary : Source file for the Death Blow Bullet On Hit effect component.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Components/BulletDeathBlowEffectComponent.h"

#include "Characters/Unit.h"
#include "Components/CharacterStatComponent.h"


// Sets default values for this component's properties
UBulletDeathBlowEffectComponent::UBulletDeathBlowEffectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBulletDeathBlowEffectComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBulletDeathBlowEffectComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                    FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBulletDeathBlowEffectComponent::OnHit(AActor* target)
{
	Super::OnHit(target);
	TWeakObjectPtr<AActor> target_ptr = target;
	if (auto casted_target = target_ptr.Get())
	{
		auto casted_unit = Cast<AUnit>(casted_target);
		if (casted_unit->GetCharacterStat()->GetHitPoint() / casted_unit->GetCharacterStat()->GetMaxHitPoint() <= death_blow_percentage)
		{
			casted_unit->Die();
		}
	}
}
