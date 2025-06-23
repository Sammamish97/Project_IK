/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 4.22.2025
Summary : Source file for the Viper Bullet On Hit effect component.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Components/BulletViperEffectComponent.h"

#include "Abilities/ActiveSkills/ATC_ViperHexagonEffect.h"
#include "Characters/Unit.h"

void UBulletViperEffectComponent::OnHit(AActor* target)
{
	Super::OnHit(target);
	if(AUnit* casted_unit = Cast<AUnit>(target))
	{
		if (auto viper_effect = casted_unit->FindComponentByClass<UATC_ViperHexagonEffect>())
		{
			viper_effect->IncreaseStack();
		}
		else
		{
			casted_unit->AddComponentByClass(UATC_ViperHexagonEffect::StaticClass(), false, casted_unit->GetTransform(), false);
		}
	}
}
