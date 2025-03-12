/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 03.12.2025
Summary : Source file for a global buff that remains bleeding on damaged targets.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/GlobalBuffLogics/WoundingBulletsBuffLogic.h"

#include "Characters/HeroBase.h"

bool UWoundingBulletsBuffLogic::IsBuffValidOnTarget(UObject* buff_target)
{
	return buff_target->IsA<AHeroBase>();
}

void UWoundingBulletsBuffLogic::ApplyBuff(UObject* buff_target)
{
	AHeroBase* hero = Cast<AHeroBase>(buff_target);

	TArray<FOnDamage>& delegate_array = hero->hero_dmg_event_map_.FindOrAdd(EHeroEvent::OnHitBeforeCalc);
	delegate_array.AddDefaulted();
	delegate_array.Last().BindUObject(this, &UWoundingBulletsBuffLogic::ApplyBleeding);
}

FDamageData UWoundingBulletsBuffLogic::ApplyBleeding(FDamageData data)
{
	TWeakObjectPtr<AHeroBase> hero = Cast<AHeroBase>(data.attack_target);
	hero->ApplyCrowdControl(ECCType::Bleeding, 5.f);
	return data;
}
