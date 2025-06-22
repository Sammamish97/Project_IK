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
#include "Structs/BuffData.h"

#include "Components/BoxComponent.h"

#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

UAT_DeployCover::UAT_DeployCover()
{
	target_param_ = FTargetParameters(ETargetingMode::Location, ETargetType::None, 1000.f, 100.f);

	scaling_factor_ = 0.02f;
	cool_time_ = 10.f;
}

bool UAT_DeployCover::ActivateSkill_Implementation(const FTargetResult& TargetResult)
{
	FBuffData attack_speed(TEXT("DeployCover"), ECharacterStatType::AttackSpeed, 1.1, true, 10.f);

	deploy_location_ = TargetResult.target_location_;
	spawn_location_ = deploy_location_ + FVector(0.f, 0.f, deploy_height_offset_);

	if (actor_class_ && skill_owner_)
	{
		actor_ = skill_owner_->GetWorld()->SpawnActor<ACover>(actor_class_, spawn_location_, FRotator::ZeroRotator);
		if (actor_)
		{
			AUnit* owner_unit = Cast<AUnit>(skill_owner_);
			actor_->SetHitPoints(deployed_cover_hit_points_ + owner_unit->GetCharacterStat()->GetSkillPower() * hit_points_scaling_factor_);
			actor_->SetMobility(EComponentMobility::Movable);
			ApplyBuff(attack_speed, skill_owner_);
			is_deploying_ = true;
			deploying_timer_ = 0.f;

			return true;
		}
	}

	return false;
}

void UAT_DeployCover::Tick(float DeltaTime)
{
	if (is_deploying_)
	{
		if (actor_) {
			deploying_timer_ += DeltaTime;
			if (deploying_timer_ >= deploy_time_)
			{
				deploying_timer_ = deploy_time_;
				actor_->SetActorLocation(FMath::Lerp(spawn_location_, deploy_location_, deploying_timer_ / deploy_time_));

				UBoxComponent* comp = actor_->GetComponentByClass<UBoxComponent>();
				// Need to be changed if Cover's hierarchy has changed.
				FVector offset = FVector(0.f, 0.f, actor_->GetRootComponent()->GetComponentLocation().Z - comp->GetComponentLocation().Z);
				UNiagaraFunctionLibrary::SpawnSystemAttached(deploy_particle_, comp, NAME_None, offset, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, true);

				actor_->SetMobility(EComponentMobility::Static);

				is_deploying_ = false;
				deploying_timer_ = 0.f;

				actor_ = nullptr;
				return;
			}

			actor_->SetActorLocation(FMath::Lerp(spawn_location_, deploy_location_, deploying_timer_ / deploy_time_));
		}
		else
		{
			is_deploying_ = false;
			deploying_timer_ = 0.f;
		}
	}
}