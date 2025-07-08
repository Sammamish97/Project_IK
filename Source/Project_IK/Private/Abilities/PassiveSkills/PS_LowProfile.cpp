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
#include "DataAssets/BuffUIDataAsset.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/DataTableManager.h"
#include "WorldSettings/IKGameInstance.h"

void UPS_LowProfile::InitEquipmentSkill(AActor* hero_ref)
{
	Super::InitEquipmentSkill(hero_ref);

	hero_ref->GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnUnitEvent(hero_ref, EUnitEvent::HideOnCover, this, &UPS_LowProfile::RemoveBuff);
	hero_ref->GetWorld()->GetSubsystem<UDelegateBridgeSubsystem>()->BindOnUnitEvent(hero_ref, EUnitEvent::LeaveCover, this, &UPS_LowProfile::ApplyBuff);
	
	if (AHeroBase* hero = Cast<AHeroBase>(hero_ref))
	{
		AttachParticles(hero->GetMesh());
	}
	buff_status_data_ = FBuffStatusData(ECharacterStatType::EvasionRate, 0.1f, false, true);
	auto data_table_manager_ = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GetDataTableManager();
	buff_ui_data_ = data_table_manager_->GetBuffUIData(EBuffType::LowProfile);

	ApplyBuff();
}

void UPS_LowProfile::ApplyBuff()
{
	if (is_buff_applied_ == false)
	{
		AActor* actor = hero_cache_.Get();
		if (actor)
		{
			AHeroBase* unit = Cast<AHeroBase>(actor);
			if (unit)
			{
				unit->ApplyBuff(EBuffType::LowProfile, buff_status_data_);
				unit->AddBuffUI(buff_ui_data_);
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
		AActor* actor = hero_cache_.Get();
		if (actor)
		{
			AHeroBase* unit = Cast<AHeroBase>(actor);
			if (unit)
			{
				unit->RemoveBuff(EBuffType::LowProfile);
				unit->RemoveBuffUI(EBuffType::LowProfile);
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
