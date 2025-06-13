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
#include "Structs/BuffData.h"
#include "Characters/Unit.h"

#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Components/CapsuleComponent.h"

void UPS_Agility::InitEquipmentSkill(AActor* hero_ref)
{
	Super::InitEquipmentSkill(hero_ref);

	hero_ref->GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnActiveSkill(this, &UPS_Agility::BuffAttackSpeed);
	SpawnParticles(Cast<AUnit>(hero_ref));
}

void UPS_Agility::BuffAttackSpeed(EHeroType hero_idx)
{
	FBuffData attack_speed(TEXT("AgilityBuff"), ECharacterStatType::AttackSpeed, buff_amount_, is_buff_percentage_, buff_duration_);

	AActor* hero_actor = hero_cache_.Get();
	if (hero_actor)
	{
		AHeroBase* hero = Cast<AHeroBase>(hero_actor);
		if (hero->GetHeroType() == hero_idx)
		{
			hero->ApplyBuff(attack_speed);

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
