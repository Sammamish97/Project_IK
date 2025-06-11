// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/SkillBase.h"

#include "Kismet/GameplayStatics.h"
#include "WorldSettings/IKPlayerController.h"

void USkillBase::InitSkill()
{
	player_controller_cache_ = Cast<AIKPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

FTargetParameters USkillBase::GetTargetParameters() const
{
	return target_param_;
}

float USkillBase::GetCoolTime() const
{
	return cool_time_;
}

bool USkillBase::ActivateSkill()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(cool_down_handle_) == false)
	{
		player_controller_cache_->StartTargeting(target_param_);
		return true;
	}
	return false;
}

void USkillBase::Decide(const FTargetResult& TargetResult)
{
}

void USkillBase::Reset()
{
}

void USkillBase::OnDecide()
{
	player_controller_cache_->ClearTargetingState();
	Reset();
	BeginCoolDown();
	on_decide_.Broadcast(cool_time_);
}

void USkillBase::BeginCoolDown()
{
	if (GetWorld()->GetTimerManager().IsTimerActive(cool_down_handle_) == false)
	{
		GetWorld()->GetTimerManager().SetTimer(cool_down_handle_, cool_time_, false);
	}
}
