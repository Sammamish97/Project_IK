/******************************************************************************
Copyright(C) 2025
Author: Sinil Kang (rtd99062@gmail.com)
Creation Date : 5.2.2025
Summary : Source file for the low profile passive skill.
					It gives evasion rate buffs when they are not in cover.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/PassiveSkills/PS_LowProfile.h"

#include "Subsystems/DelegateBridgeSubsystem.h"

#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

#include "Characters/HeroBase.h"

#include "Managers/DataTableManager.h"

void UPS_LowProfile::InitPassiveSkill(AActor* hero_ref, const FPassiveSkillData& skill_data)
{
	Super::InitPassiveSkill(hero_ref, skill_data);

	//hero_ref->GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnUnitEvent(hero_ref, EUnitEvent::HideOnCover, this, &UPS_LowProfile::RemoveBuff);
	//hero_ref->GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnUnitEvent(hero_ref, EUnitEvent::LeaveCover, this, &UPS_LowProfile::ApplyBuff);
	
	if (AHeroBase* hero = Cast<AHeroBase>(hero_ref))
	{
		AttachParticles(hero->GetMesh());
	}
	buff_status_data_ = FBuffStatusData(ECharacterStatType::EvasionRate, 0.1f, false, true);
	ApplyBuff();
}

void UPS_LowProfile::ApplyBuff()
{
	if (is_buff_applied_ == false)
	{
		if (AActor* actor = hero_cache_.Get())
		{
			if (AHeroBase* hero = Cast<AHeroBase>(actor))
			{
				//hero->ApplyStatusBuff(EBuffType::LowProfile, buff_status_data_);
				//hero->AddBuffUI(FBuffUIData(skill_data_.item_data_, EBuffType::LowProfile, buff_status_data_.duration_, true));

				ActivateParticles();
				is_buff_applied_ = true;
			}
		}
	}
}

void UPS_LowProfile::RemoveBuff()
{
	if (is_buff_applied_)
	{
		if (AActor* actor = hero_cache_.Get())
		{
			if (AHeroBase* unit = Cast<AHeroBase>(actor))
			{
				//unit->RemoveBuff(EBuffType::LowProfile);
				//unit->RemoveBuffUI(EBuffType::LowProfile);
				DeactivateParticles();
				is_buff_applied_ = false;
			}
		}
	}
}

void UPS_LowProfile::AttachParticles(USceneComponent* attached_component)
{
	left_elbow_particle_ = UNiagaraFunctionLibrary::SpawnSystemAttached(skill_particle_system_, attached_component, FName("elbowtrailsocket_l"), FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, false, false);
	right_elbow_particle_ = UNiagaraFunctionLibrary::SpawnSystemAttached(skill_particle_system_, attached_component, FName("elbowtrailsocket_r"), FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, false, false);
	left_foot_particle_ = UNiagaraFunctionLibrary::SpawnSystemAttached(skill_particle_system_, attached_component, FName("foottrailsocket_l"), FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, false, false);
	right_foot_particle_ = UNiagaraFunctionLibrary::SpawnSystemAttached(skill_particle_system_, attached_component, FName("foottrailsocket_r"), FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, false, false);
}

void UPS_LowProfile::ActivateParticles()
{
	if (left_elbow_particle_ && right_elbow_particle_ &&
		left_foot_particle_ && right_foot_particle_)
	{
		left_elbow_particle_->Activate(true);
		right_elbow_particle_->Activate(true);
		left_foot_particle_->Activate(true);
		right_foot_particle_->Activate(true);
	}
}

void UPS_LowProfile::DeactivateParticles()
{
	if (left_elbow_particle_ && right_elbow_particle_ &&
		left_foot_particle_ && right_foot_particle_)
	{
		left_elbow_particle_->Deactivate();
		right_elbow_particle_->Deactivate();
		left_foot_particle_->Deactivate();
		right_foot_particle_->Deactivate();
	}
}
