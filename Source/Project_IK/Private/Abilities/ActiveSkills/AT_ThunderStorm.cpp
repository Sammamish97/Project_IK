/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 04.18.2025
Summary : Source file for an active skill named ThunderStorm.
					It periodically summons thunders that damages in an area.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Abilities/ActiveSkills/AT_ThunderStorm.h"

#include "Structs/TargetResult.h"

#include "Abilities/ActiveSkills/ThunderStorm.h"
#include "Characters/Unit.h"

UAT_ThunderStorm::UAT_ThunderStorm()
{
	target_param_ = FTargetParameters(ETargetingMode::Location, ETargetType::Opponents, 1000.f, 2000.f);

	has_casting_motion_ = true;
	casting_time_ = 0.5f;
	ai_holding_time_ = 1.5f;
}

void UAT_ThunderStorm::InitActiveSkill(AActor* skill_owner, const FActiveSkillData& skill_data)
{
	Super::InitActiveSkill(skill_owner, skill_data);
	if (IsUpgradedActiveSkill(skill_data_.type_))
	{
		//IKTODO: 만약 A면 번개가 6번 치면 좋겠음.
	}
}

bool UAT_ThunderStorm::CanActivateSkill(const FTargetResult& TargetResult)
{
	return visual_actor_class_ != nullptr;
}

bool UAT_ThunderStorm::ActivateSkill(const FTargetResult& TargetResult)
{
	FActorSpawnParameters spawn_params;
	spawn_params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	visual_actor_ = skill_owner_->GetWorld()->SpawnActor<AThunderStorm>(visual_actor_class_, TargetResult.target_location_, FRotator::ZeroRotator, spawn_params);
	if (visual_actor_)
	{
		visual_actor_->SetNecessaryData(target_param_.radius_, skill_data_.skill_power_scales_[0], damage_, skill_owner_);
		return Super::ActivateSkill(TargetResult);
	}
	return false;
}

void UAT_ThunderStorm::OnEnterCasting()
{
	Super::OnEnterCasting();
	Cast<AUnit>(skill_owner_)->PlayAnimMontage(casting_anim_montage_);
}