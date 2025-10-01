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

#include "NiagaraFunctionLibrary.h"
#include "Kismet/KismetMathLibrary.h"

void UBulletDeathBlowEffectComponent::OnHit(AActor* target, const FHitResult& hit_result)
{
	Super::OnHit(target, hit_result);
	TWeakObjectPtr<AActor> target_ptr = target;
	if (auto casted_target = target_ptr.Get())
	{
		auto casted_unit = Cast<AUnit>(casted_target);
		if (casted_unit &&
			casted_unit->GetCharacterStat()->GetHitPoint() / casted_unit->GetCharacterStat()->GetMaxHitPoint() <= death_blow_percentage_)
		{
			UAudioManagerSubsystem::Get(this)->PlayAtLocation(EAudioType::Deathblow, casted_unit->GetActorLocation());
			casted_unit->Die();

			SpawnBleedingParticle(target, hit_result);
		}
	}
}

void UBulletDeathBlowEffectComponent::SpawnBleedingParticle(AActor* target, const FHitResult& hit_result)
{
	if (!bleeding_particle_)
	{
		return;
	}

	const FRotator facing = UKismetMathLibrary::MakeRotFromZ(hit_result.ImpactNormal);

	USceneComponent* attach_comp = hit_result.GetComponent();

	const FName attach_bone = hit_result.BoneName;

	UNiagaraFunctionLibrary::SpawnSystemAttached(
		bleeding_particle_,
		attach_comp,
		attach_bone,
		hit_result.ImpactPoint,
		facing,
		EAttachLocation::KeepWorldPosition,
		true
	);
}
