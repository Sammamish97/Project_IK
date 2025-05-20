/******************************************************************************
Copyright(C) 2025
Author: Sinil Kang (rtd99062@gmail.com)
Creation Date : 4.28.2025
Summary : Source file for the berserker passive skill.
					It gives life steal and attack speed buffs.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/PassiveSkills/PS_Berserker.h"

#include "Subsystems/DelegateBridgeSubsystem.h"
#include "Structs/BuffData.h"
#include "Characters/Unit.h"

#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/CapsuleComponent.h"

void UPS_Berserker::InitEquipmentSkill(AActor* hero_ref)
{
	Super::InitEquipmentSkill(hero_ref);

	AUnit* unit = Cast<AUnit>(hero_ref);
	if (unit)
	{
		hero_ref->GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnHPChanged(unit->GetCharacterStat(), this, &UPS_Berserker::BuffBerserker);

		SpawnParticles(unit);
	}
}

void UPS_Berserker::BuffBerserker(float hp_ratio)
{
	// If buff applied & current hp is above the threshold -> REMOVE
	if (is_buff_applied_)
	{
		if (hp_ratio > hp_ratio_threshold_)
		{
			RemoveBuff();
		}
	}
	// If buff NOT applied & current hp is below the threshold -> APPLY
	else
	{
		if (hp_ratio < hp_ratio_threshold_)
		{
			ApplyBuff();
		}
	}
}

void UPS_Berserker::ApplyBuff()
{
	if (is_buff_applied_ == false)
	{
		AActor* actor = hero_cache_.Get();
		if (actor)
		{
			AUnit* unit = Cast<AUnit>(actor);
			if (unit)
			{
				FBuffData life_steal(TEXT("Berserker_lifesteal"), ECharacterStatType::LifeSteal, life_steal_buff_amount_, false, true);
				FBuffData attack_speed(TEXT("Berserker_attack_speed"), ECharacterStatType::AttackSpeed, attack_speed_buff_amount_, is_attack_speed_buff_percentage_, true);
				unit->ApplyBuff(life_steal);
				unit->ApplyBuff(attack_speed);

				ActivateParticles();

				is_buff_applied_ = true;
			}
		}
	}
}

void UPS_Berserker::RemoveBuff()
{
	if (is_buff_applied_)
	{
		AActor* actor = hero_cache_.Get();
		if (actor)
		{
			AUnit* unit = Cast<AUnit>(actor);
			if (unit)
			{
				unit->RemoveBuff(TEXT("Berserker_lifesteal"));
				unit->RemoveBuff(TEXT("Berserker_attack_speed"));

				DeactivateParticles();

				is_buff_applied_ = false;
			}
		}
	}
}

void UPS_Berserker::SpawnParticles(AUnit* actor)
{
	USceneComponent* component = actor->GetRootComponent();
	berserker_particle_component_ = UNiagaraFunctionLibrary::SpawnSystemAttached(skill_particle_system_, component, FName(), FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, false, false);
	
	UCapsuleComponent* capsule_component = Cast<UCapsuleComponent>(component);
	if (capsule_component)
	{
		berserker_particle_component_->SetVariableFloat(FName("Cylinder Height"), capsule_component->GetUnscaledCapsuleHalfHeight() * 2.f);
		berserker_particle_component_->SetVariableFloat(FName("Cylinder Radius"), capsule_component->GetUnscaledCapsuleRadius());
	}
}

void UPS_Berserker::ActivateParticles()
{
	if (berserker_particle_component_)
	{
		berserker_particle_component_->Activate();
	}
}

void UPS_Berserker::DeactivateParticles()
{
	if (berserker_particle_component_)
	{
		berserker_particle_component_->Deactivate();
	}
}
