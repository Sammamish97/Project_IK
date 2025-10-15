/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.22.2025
Summary : Header file for Thunder Active Skill.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Abilities/ActiveSkills/AT_Thunder.h"

#include "Characters/Unit.h"

#include "Subsystems/AudioManagerSubsystem.h"

#include "NiagaraFunctionLibrary.h"

UAT_Thunder::UAT_Thunder()
{
	target_param_ = FTargetParameters(ETargetingMode::Actor, ETargetType::Opponents, 1000.f);
	damage_ = 100.f;
}

void UAT_Thunder::OnEnterCasting()
{
	Super::OnEnterCasting();
	Cast<AUnit>(skill_owner_)->PlayAnimMontage(casting_anim_montage_);
}

void UAT_Thunder::PlaySFX(const FVector& location)
{
	GetWorld()->GetGameInstance()->GetSubsystem<UAudioManagerSubsystem>()->PlayAtLocation(EAudioType::ThunderZap, location);
}

void UAT_Thunder::PlayVFX(const FVector& location)
{
	if (zap_vfx_)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), zap_vfx_, location);
	}
}

void UAT_Thunder::InitActiveSkill(AActor* skill_owner, const FActiveSkillData& skill_data)
{
	Super::InitActiveSkill(skill_owner, skill_data);
	if (IsUpgradedActiveSkill(skill_data_.type_))
	{
		cool_time_ -= 2;
	}
}

bool UAT_Thunder::ActivateSkill(const FTargetResult& target_result)
{
	if(target_result.target_actors_.IsEmpty() == false && target_result.target_actors_[0])
	{
		FVector location = target_result.target_actors_[0]->GetActorLocation();

		AUnit* unit = Cast<AUnit>(target_result.target_actors_[0]);
		if (unit)
		{
			location = location + unit->GetMesh()->GetRelativeLocation();
		}
		PlaySFX(location);
		PlayVFX(location);

		ApplyDamage({ 0, damage_, EDamageType::Magic, skill_owner_, target_result.target_actors_[0] });
	}
	return Super::ActivateSkill(target_result);
}
