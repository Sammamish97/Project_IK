/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.30.2024
Summary : Source file for GameState.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Worldsettings/IKGameState.h"

#include "Abilities/SupportSkills/SupportSkillBase.h"
#include "Components/EnergySystemComponent.h"
#include "Structs/SupportSkillData.h"

AIKGameState::AIKGameState()
	:Super::AGameStateBase()
{
	energy_system_component_ = CreateDefaultSubobject<UEnergySystemComponent>(TEXT("Energy System Component"));
	support_skill_data_.Init(FSupportSkillData(), 3);
	equipped_support_skills_.Init(TObjectPtr<USupportSkillBase>(), 3);
}

void AIKGameState::BeginPlay()
{
	Super::BeginPlay();
	for (int32 i = 0; i < 3; i++)
	{
		if (support_skill_data_[i].type_ != ESupportSkillType::INVALID)
		{
			equipped_support_skills_[i] = NewObject<USupportSkillBase>(this, support_skill_data_[i].support_skill_class_);
			equipped_support_skills_[i]->InitSupportSkill();
		}
	}
}

void AIKGameState::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	equipped_support_skills_.Empty();
}

bool AIKGameState::UseEnergy(float amount)
{
	return energy_system_component_->UseEnergy(amount);
}

const TArray<FSupportSkillData>& AIKGameState::GetSupportSkillData() const
{
	return support_skill_data_;
}

const TArray<TObjectPtr<USupportSkillBase>>& AIKGameState::GetSupportSkillPtr() const
{
	return equipped_support_skills_;
}

UEnergySystemComponent* AIKGameState::GetEnergySystemComponent()
{
	return energy_system_component_;
}

void AIKGameState::ActivateSupportSkill(int32 support_num)
{
	if (equipped_support_skills_.IsValidIndex(support_num))
	{
		if (energy_system_component_->GetEnergy() >  equipped_support_skills_[support_num]->GetCost())
		{
			last_invoked_support_skill_ = equipped_support_skills_[support_num];
			last_invoked_support_skill_->ActivateSkill();
		}
	}
}

void AIKGameState::DecideLastInvokedSkill(FTargetResult target_result)
{
	last_invoked_support_skill_->Decide(target_result);
}

void AIKGameState::ClearLastInvokedSkill()
{
	if (last_invoked_support_skill_)
	{
		last_invoked_support_skill_->Reset();
	}
}
