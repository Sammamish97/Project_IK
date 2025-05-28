/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 3.9.2025
Summary : Source file for the Set Bonus Base.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/SetBonuses/SetBonusBase.h"

#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/CapsuleComponent.h"

#include "Characters/HeroBase.h"

void USetBonusBase::ActivateSetBonus(TObjectPtr<AHeroBase> owner, int32 set_amount)
{
	hero_cache_ = owner;
	if (set_amount == 2)
	{
		ActivateEdgeBonus();
	}
	else if (set_amount == 3)
	{
		ActivateTriangleBonus();
	}
	else if (set_amount == 6)
	{
		ActivateHexagonBonus();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Wrong node amount for the Set Bonus!"));
	}

	if (set_amount >= 2)
	{
		SpawnNiagara(owner.Get());
	}
}

void USetBonusBase::ActivateEdgeBonus()
{
}

void USetBonusBase::ActivateTriangleBonus()
{
}

void USetBonusBase::ActivateHexagonBonus()
{
}

void USetBonusBase::SpawnNiagara(AHeroBase* hero)
{
	if (rune_particle_ && hero)
	{
		USceneComponent* component = hero->GetRootComponent();
		const UCapsuleComponent* capsule = Cast<UCapsuleComponent>(component);
		const FVector offset = FVector(0.0, 0.0, capsule->GetUnscaledCapsuleHalfHeight() * 1.5);
		UNiagaraComponent* niagara = UNiagaraFunctionLibrary::SpawnSystemAttached(rune_particle_, component, FName(), offset, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, true);
	}
}
