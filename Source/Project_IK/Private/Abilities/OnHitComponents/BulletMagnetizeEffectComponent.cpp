/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.12.2025
Summary : Source file for the Bullet Magnetize Effect On Hit effect component.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/OnHitComponents/BulletMagnetizeEffectComponent.h"

#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Abilities/ActiveSkills/ATC_MagnetizedEffect.h"
#include "Characters/HeroBase.h"
#include "Characters/Unit.h"
#include "Components/CharacterStatComponent.h"
#include "Weapons/Guns/Bullet.h"

class UNiagaraComponent;

void UBulletMagnetizeEffectComponent::OnHit(AActor* target, const FHitResult& hit_result)
{
	Super::OnHit(target, hit_result);
	if (AUnit* target_unit = Cast<AUnit>(target))
	{
		auto shooter = GetOwner<ABullet>()->GetShooter();
		if (auto hero = Cast<AHeroBase>(shooter))
		{
			FDamageData dmg_data = {0.f, 0.f, EDamageType::Projectile, hero,target_unit};
			dmg_data.skill_power_base_dmg_ = hero->GetCharacterStat()->GetSkillPower() * skill_power_scale_;
			target_unit->GetDamage(dmg_data);
			if (auto magnetized_effect = target_unit->FindComponentByClass<UATC_MagnetizedEffect>())
			{
				magnetized_effect->IncreaseStack();
			}
			else
			{
				target_unit->AddComponentByClass(UATC_MagnetizedEffect::StaticClass(), false, target_unit->GetTransform(), false);
			}
		}
	}
}

void UBulletMagnetizeEffectComponent::ApplyEffect(ABullet* bullet) const
{
	if (on_hit_effect_)
	{
		UNiagaraComponent* component = UNiagaraFunctionLibrary::SpawnSystemAttached(on_hit_effect_, bullet->GetSceneComponent(), NAME_None, FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, false);
		component->SetVariableFloat(FName("SphereRadius"), 10.f);
	}
	if (on_hit_material_)
	{
		bullet->ApplyMaterial(0, on_hit_material_);
	}
}
