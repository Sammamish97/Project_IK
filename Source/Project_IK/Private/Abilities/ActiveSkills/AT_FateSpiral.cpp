/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 04.21.2025
Summary : Source file for an active skill named FateSpiral.
					It dispatches a wave that travels from an ally to an enemy and back again. 
					It damages enemies it touches and heals allies when it returns.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/ActiveSkills/AT_FateSpiral.h"

#include "Abilities/ActiveSkills/FateSpiral.h"
#include "Structs/TargetParameters.h"
#include "Structs/TargetResult.h"

UAT_FateSpiral::UAT_FateSpiral()
{
	target_param_ = FTargetParameters(ETargetingMode::Actor, ETargetType::All, 1000.f);

	cool_time_ = 10;
}

void UAT_FateSpiral::Decide(const FTargetResult& TargetResult)
{
	OnDecide();
	if (actor_class_)
	{
		actor_ = skill_owner_->GetWorld()->SpawnActor<AFateSpiral>(actor_class_);

		actor_->SetSkillOwner(skill_owner_);
		actor_->SetDepartureActor(skill_owner_);
		actor_->SetArrivalActor(TargetResult.target_actors_[0]);
		actor_->SetRange(target_param_.range_);
	}
}
