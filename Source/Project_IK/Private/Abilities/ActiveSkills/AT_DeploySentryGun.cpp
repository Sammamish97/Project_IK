/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 04.22.2025
Summary : Source file for an active skill named DeployCover.
					It deploys a sentry gun on the battlefield.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/ActiveSkills/AT_DeploySentryGun.h"

#include "Characters/Unit.h"
#include "Components/CharacterStatComponent.h"

#include "Structs/TargetParameters.h"
#include "Structs/TargetResult.h"
#include "Weapons/Skills/SentryGun.h"

UAT_DeploySentryGun::UAT_DeploySentryGun()
{
	target_param_ = FTargetParameters(ETargetingMode::Location, ETargetType::None, 1000.f, 100.f);

	cool_time_ = 15.f;
}

void UAT_DeploySentryGun::OnEnterCasting()
{
	Super::OnEnterCasting();
	Cast<AUnit>(skill_owner_)->PlayAnimMontage(casting_anim_montage_);
}

bool UAT_DeploySentryGun::ActivateSkill(const FTargetResult& TargetResult)
{
	if (sentry_gun_class_)
	{
		AUnit* owner_unit = Cast<AUnit>(skill_owner_);
		UCharacterStatComponent* stat_component_cache = owner_unit->GetCharacterStat();
		sentry_gun_actor_ = skill_owner_->GetWorld()->SpawnActor<ASentryGun>(sentry_gun_class_, TargetResult.target_location_, FRotator::ZeroRotator);
		sentry_gun_actor_->InitSentryGun(IsUpgradedActiveSkill(skill_data_.type_),stat_component_cache->GetSkillPower());
	}
	return Super::ActivateSkill(TargetResult);
}
