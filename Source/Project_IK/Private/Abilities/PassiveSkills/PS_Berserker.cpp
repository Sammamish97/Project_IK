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
#include "Characters/Unit.h"

#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Abilities/Buffs/BuffBase.h"
#include "Components/CapsuleComponent.h"

#include "Managers/DataTableManager.h"

void UPS_Berserker::InitPassiveSkill(AActor* hero_ref, const FPassiveSkillData& skill_data)
{
	Super::InitPassiveSkill(hero_ref, skill_data);
	AUnit* unit = Cast<AUnit>(hero_ref);
	if (unit)
	{
		hero_ref->GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnHPChanged(unit->GetCharacterStat(), this, &UPS_Berserker::BuffBerserker);
		SpawnParticles(unit);
	}
	buff_ = NewObject<UBuffBase>(this, buff_class_);
}

void UPS_Berserker::BuffBerserker(float hp_ratio)
{
	// If buff applied & current hp is above the threshold -> REMOVE
	if (is_buff_applied_)
	{
		if (hp_ratio > hp_ratio_threshold_)
		{
			buff_->RemoveBuff(Cast<AUnit>(hero_cache_));
			DeactivateParticles();
			is_buff_applied_ = false;
		}
	}
	// If buff NOT applied & current hp is below the threshold -> APPLY
	else
	{
		if (hp_ratio < hp_ratio_threshold_)
		{
			buff_->ApplyBuff(Cast<AUnit>(hero_cache_));
			ActivateParticles();
			is_buff_applied_ = true;
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
