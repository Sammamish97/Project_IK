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
#include "Structs/BuffStatusData.h"

void UBulletDebuffEffectComponent::OnHit(AActor* target)
{
	Super::OnHit(target);
	TWeakObjectPtr<AActor> target_ptr = target;
	if (auto casted_target = target_ptr.Get())
	{
		auto casted_unit = Cast<AUnit>(casted_target);
		//IKTODO: 테스트 후 버프 적용
		//casted_unit->ApplyBuff(FBuffStatusData(FName("TriangleSetBonus_Viper"), ECharacterStatType::Armor, debuff_amount_, true, debuff_duration_));
	}
}
