/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.21.2025
Summary : Source file for the Death Blow Bullet On Hit effect component.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Abilities/OnHitComponents/BulletDeathBlowEffectComponent.h"

#include "Characters/Unit.h"
#include "Components/CharacterStatComponent.h"

#include "Subsystems/AudioManagerSubsystem.h"
void UBulletDeathBlowEffectComponent::OnHit(AActor* target)
{
	Super::OnHit(target);
	TWeakObjectPtr<AActor> target_ptr = target;
	if (auto casted_target = target_ptr.Get())
	{
		auto casted_unit = Cast<AUnit>(casted_target);
		if (casted_unit->GetCharacterStat()->GetHitPoint() / casted_unit->GetCharacterStat()->GetMaxHitPoint() <= death_blow_percentage_)
		{
			UAudioManagerSubsystem::Get(this)->PlayAtLocation(EAudioType::Deathblow, casted_unit->GetActorLocation());
			casted_unit->Die();
		}
	}
}
