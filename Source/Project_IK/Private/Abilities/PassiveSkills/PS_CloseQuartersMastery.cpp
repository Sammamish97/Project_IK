/******************************************************************************
Copyright(C) 2025
Author: Sinil Kang (rtd99062@gmail.com)
Creation Date : 4.28.2025
Summary : Source file for the CloseQuatersMastery passive skill.
					It gives high critical rate if damaged enemy is nearby.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/PassiveSkills/PS_CloseQuartersMastery.h"

#include "Subsystems/DelegateBridgeSubsystem.h"
#include "Characters/HeroBase.h"
#include "Structs/DamageData.h"

void UPS_CloseQuartersMastery::InitEquipmentSkill(AActor* hero_ref)
{
	Super::InitEquipmentSkill(hero_ref);

	bool bind_result = hero_ref->GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnCriticalRateCalculation(hero_ref, this, &UPS_CloseQuartersMastery::CloseQuatersMastery);
	if (bind_result == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("BindOnCriticalRateCalculation has failed in UPS_CloseQuartersMastery::InitEquipmentSkill."));
		check(TEXT("BindOnCriticalRateCalculation has failed in UPS_CloseQuartersMastery::InitEquipmentSkill."));
	}
}

void UPS_CloseQuartersMastery::CloseQuatersMastery(float& critical_rate)
{
	AActor* actor = hero_cache_.Get();
	if (actor)
	{
		AHeroBase* hero = Cast<AHeroBase>(actor);
		if (hero)
		{
			AActor* target = hero->GetAttackTarget();
			if (target)
			{
				float weapon_range = hero->GetWeaponMechanics()->GetWeaponData().fire_range;

				float bonus_critical_rate = max_critical_rate_bonus_ * (1 - (GetDistance2D(hero, target, weapon_range) / weapon_range));
				critical_rate += bonus_critical_rate;
			}
		}
	}
}

float UPS_CloseQuartersMastery::GetDistance2D(const AActor* hero, const AActor* target, float weapon_range)
{
	if (!hero || !target)
	{
		return 0.0f;
	}

	FVector hero_location = hero->GetActorLocation();
	FVector target_location = target->GetActorLocation();

	// Ignore Z-axis
	FVector2D hero_location_2D(hero_location.X, hero_location.Y);
	FVector2D target_location_2D(target_location.X, target_location.Y);

	float distance = FVector2D::Distance(hero_location_2D, target_location_2D);

	return FMath::Min(distance, weapon_range);
}