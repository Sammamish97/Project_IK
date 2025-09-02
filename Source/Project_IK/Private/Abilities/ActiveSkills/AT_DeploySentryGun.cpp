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
#include "Components/CapsuleComponent.h"

#include "NiagaraFunctionLibrary.h"

UAT_DeploySentryGun::UAT_DeploySentryGun()
{
	target_param_ = FTargetParameters(ETargetingMode::Location, ETargetType::None, 1000.f, 100.f);
}

void UAT_DeploySentryGun::OnEnterCasting()
{
	Super::OnEnterCasting();
	Cast<AUnit>(skill_owner_)->PlayAnimMontage(casting_anim_montage_);
}

void UAT_DeploySentryGun::Tick(float DeltaTime)
{
	if (is_deploying_)
	{
		if (sentry_gun_actor_)
		{
			deploying_timer_ += DeltaTime;
			if (deploying_timer_ >= deploy_time_)
			{
				deploying_timer_ = deploy_time_;
				// sentry_gun_actor_->SetActorLocation(deploying_location_);

				UCapsuleComponent* component = sentry_gun_actor_->GetComponentByClass<UCapsuleComponent>();
				if (component)
				{
					float half_height =  component->GetScaledCapsuleHalfHeight();

					UNiagaraFunctionLibrary::SpawnSystemAttached(deploy_particle_, sentry_gun_actor_->GetRootComponent(), FName(""), FVector(0.f, 0.f, -half_height), FRotator::ZeroRotator, EAttachLocation::SnapToTarget, true);
				}

				is_deploying_ = false;
				deploying_timer_ = 0.f;

				return;
			}
			sentry_gun_actor_->SetActorLocation(FMath::Lerp(spawn_location_, deploying_location_, deploying_timer_ / deploy_time_));
		}
	}
}

bool UAT_DeploySentryGun::ActivateSkill(const FTargetResult& TargetResult)
{
	deploying_location_ = TargetResult.target_location_;
	spawn_location_ = deploying_location_ + FVector(0.f, 0.f, deploying_height_offset_);

	if (sentry_gun_class_)
	{
		AUnit* owner_unit = Cast<AUnit>(skill_owner_);
		auto owner_pos = owner_unit->GetActorLocation();
		UCharacterStatComponent* stat_component_cache = owner_unit->GetCharacterStat();
		if (stat_component_cache)
		{
			FActorSpawnParameters params;
			params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn; // or AlwaysSpawn
			sentry_gun_actor_ = skill_owner_->GetWorld()->SpawnActor<ASentryGun>(sentry_gun_class_, spawn_location_, FRotator::ZeroRotator, params);
			if (sentry_gun_actor_)
			{
				sentry_gun_actor_->InitSentryGun(IsUpgradedActiveSkill(skill_data_.type_), stat_component_cache->GetSkillPower());

				is_deploying_ = true;
				deploying_timer_ = 0.f;



				UCapsuleComponent* component = sentry_gun_actor_->GetComponentByClass<UCapsuleComponent>();
				if (component)
				{
					float half_height = component->GetScaledCapsuleHalfHeight();
					deploying_location_.Z += half_height;
				}
			}
		}
	}
	return Super::ActivateSkill(TargetResult);
}
