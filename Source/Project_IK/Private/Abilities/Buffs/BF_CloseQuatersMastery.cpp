/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.28.2025
Summary : Source file for the Close Quaters Mastery  passive skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/Buffs/BF_CloseQuatersMastery.h"
#include "Subsystems/DelegateBridgeSubsystem.h"
#include "Characters/HeroBase.h"

void UBF_CloseQuatersMastery::ApplyBuff(AUnit* target)
{
	target_cache_ = target;
	bool bind_result = GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnCriticalRateCalculation(target, this, &UBF_CloseQuatersMastery::CloseQuatersMastery);
	if (bind_result == false)
	{
		UE_LOG(LogTemp, Warning, TEXT("BindOnCriticalRateCalculation has failed in UPS_CloseQuartersMastery::InitEquipmentSkill."));
		check(TEXT("BindOnCriticalRateCalculation has failed in UPS_CloseQuartersMastery::InitEquipmentSkill."));
	}
	target->AddBuffUI(buff_type_);
}

void UBF_CloseQuatersMastery::CloseQuatersMastery(float& critical_rate)
{
	if (AActor* actor = target_cache_.Get())
	{
		if (AHeroBase* hero = Cast<AHeroBase>(actor))
		{
			if (AActor* target = hero->GetAttackTarget())
			{
				float weapon_range = hero->GetWeaponMechanics()->GetWeaponData().fire_range;
				float distance_2d = FMath::Min(FVector::Dist2D(hero->GetActorLocation(), target->GetActorLocation()), weapon_range);
				float bonus_critical_rate = max_critical_rate_bonus_ * (1 - distance_2d / weapon_range);
				critical_rate += bonus_critical_rate;
			}
		}
	}
}