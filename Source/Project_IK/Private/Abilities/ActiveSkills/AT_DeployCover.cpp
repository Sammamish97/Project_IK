/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 04.22.2025
Summary : Source file for an active skill named DeployCover.
					It deploys a cover on the battlefield.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/ActiveSkills/AT_DeployCover.h"

#include "Environments/Cover.h"

#include "Characters/Unit.h"
#include "Components/CharacterStatComponent.h"

#include "Structs/TargetParameters.h"
#include "Structs/TargetResult.h"
#include "Structs/BuffStatusData.h"

UAT_DeployCover::UAT_DeployCover()
{
	target_param_ = FTargetParameters(ETargetingMode::Location, ETargetType::None, 1000.f, 100.f);

	scaling_factor_ = 0.02f;
	cool_time_ = 10.f;
}

bool UAT_DeployCover::ActivateSkill(const FTargetResult& TargetResult)
{
	//IKTODO: 테스트 후 버프 적용
	// FBuffStatusData attack_speed(TEXT("DeployCover"), ECharacterStatType::AttackSpeed, 1.1, true, 10.f);
	//
	// if (actor_class_ && skill_owner_)
	// {
	// 	actor_ = skill_owner_->GetWorld()->SpawnActor<ACover>(actor_class_, TargetResult.target_location_, FRotator::ZeroRotator);
	// 	AUnit* owner_unit = Cast<AUnit>(skill_owner_);
	// 	actor_->SetHitPoints(deployed_cover_hit_points_ + owner_unit->GetCharacterStat()->GetSkillPower() * hit_points_scaling_factor_);
	// 	ApplyBuff(attack_speed, skill_owner_);
	// }
	return Super::ActivateSkill(TargetResult);
}
