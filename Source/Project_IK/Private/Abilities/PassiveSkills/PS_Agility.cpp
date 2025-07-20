/******************************************************************************
Copyright(C) 2025
Author: Sinil Kang (rtd99062@gmail.com)
Creation Date : 4.25.2025
Summary : Source file for the agility skill.
					It buffs attack speed rate after active skill is invoked.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/PassiveSkills/PS_Agility.h"

#include "Subsystems/DelegateBridgeSubsystem.h"
#include "Characters/Unit.h"

#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Managers/DataTableManager.h"

void UPS_Agility::InitPassiveSkill(AActor* hero_ref, const FPassiveSkillData& skill_data)
{
	Super::InitPassiveSkill(hero_ref, skill_data);
	hero_ref->GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnUnitEvent(hero_ref, EUnitEvent::OnActiveSkill, this, &UPS_Agility::BuffAttackSpeed);

	buff_duration_ = 3.f;
	buff_amount_ = 2.0f;
	buff_status_data_ = FBuffStatusData(ECharacterStatType::AttackSpeed, buff_amount_, true, false, buff_duration_);

	SpawnParticles(Cast<AUnit>(hero_ref));
}

void UPS_Agility::BuffAttackSpeed()
{
	 if (AActor* hero_actor = hero_cache_.Get())
	 {
	 	if(AHeroBase* hero = Cast<AHeroBase>(hero_actor))
	 	{
	 		hero->ApplyBuff(EBuffType::Agility, buff_status_data_);
	 		hero->AddBuffUI(FBuffUIData(skill_data_.item_data_, EBuffType::Berserker, buff_status_data_.duration_, true));
			ActivateParticles();

	 	}
	 }
}

void UPS_Agility::SpawnParticles(AActor* actor)
{
	USceneComponent* component = actor->GetRootComponent();
	agility_particle_component_ = UNiagaraFunctionLibrary::SpawnSystemAttached(skill_particle_system_, component, FName(), FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, false, false);

	UCapsuleComponent* capsule_component = Cast<UCapsuleComponent>(component);
	if (capsule_component)
	{
		agility_particle_component_->SetVariableFloat(FName("Cylinder Height"), capsule_component->GetUnscaledCapsuleHalfHeight() * 2.f);
		agility_particle_component_->SetVariableFloat(FName("Cylinder Radius"), capsule_component->GetUnscaledCapsuleRadius());
	}

	if (hand_particle_system_)
	{
		AHeroBase* hero = Cast<AHeroBase>(actor);
		if (hero)
		{
			USkeletalMeshComponent* mesh = hero->GetMesh();
			hand_particle_component_1_ = UNiagaraFunctionLibrary::SpawnSystemAttached(hand_particle_system_, mesh, FName("hand_socket_l"), FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, false, false);
			hand_particle_component_2_ = UNiagaraFunctionLibrary::SpawnSystemAttached(hand_particle_system_, mesh, FName("hand_socket_r"), FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, false, false);
		}
	}
}

void UPS_Agility::ActivateParticles()
{
	if (agility_particle_component_)
	{
		agility_particle_component_->Activate();
		hand_particle_component_1_->Activate();
		hand_particle_component_2_->Activate();

		hero_cache_->GetWorld()->GetTimerManager().SetTimer(particle_deactivator_, this, &UPS_Agility::DeactivateParticles, buff_duration_);
	}
}

void UPS_Agility::DeactivateParticles()
{
	if (agility_particle_component_)
	{
		agility_particle_component_->Deactivate();
		hand_particle_component_1_->Deactivate();
		hand_particle_component_2_->Deactivate();
	}
}
