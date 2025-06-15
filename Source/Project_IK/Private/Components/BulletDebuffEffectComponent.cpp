/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.22.2025
Summary : Source file for the Debuff Bullet On Hit effect component.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Components/BulletDebuffEffectComponent.h"

#include "Characters/Unit.h"
#include "Structs/BuffData.h"

void UBulletDebuffEffectComponent::OnHit(AActor* target)
{
	Super::OnHit(target);
	if (target)
	{
		auto casted_unit = Cast<AUnit>(target);
		casted_unit->ApplyBuff(FBuffData(FName("TriangleSetBonus_Viper"), ECharacterStatType::Armor, debuff_amount_, true, debuff_duration_));
	}
}
