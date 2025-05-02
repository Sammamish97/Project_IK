/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 11.03.2024
Summary : Source file for Passive Mechanics.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Abilities/PassiveMechanics.h"

#include "AIController.h"
#include "Abilities/PassiveSkill.h"
//#include "AI/PassiveGunnerAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Characters/HeroBase.h"

// Sets default values for this component's properties
UPassiveMechanics::UPassiveMechanics()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	on_banned_ = false;
}

// Called when the game starts
void UPassiveMechanics::BeginPlay()
{
	Super::BeginPlay();
	if(passive_class_)
	{
		passive_ref_ = Cast<APassiveSkill>(GetWorld()->SpawnActor(passive_class_));
		passive_ref_->Initialize(GetOwner());
	}else
	{
		UE_LOG(LogTemp, Error, TEXT("PassiveMechanics::BeginPlay Error. Passive class should be setted"));
	}
}

void UPassiveMechanics::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearTimer(hold_time_handle_);
	GetWorld()->GetTimerManager().ClearTimer(ban_time_handle_);

	Super::EndPlay(EndPlayReason);
}

void UPassiveMechanics::BeginPassive()
{
	if(IsPassiveAvailable())
	{
		ActivatePassiveSkill();
	}
}

void UPassiveMechanics::BanPassive(float duration)
{
	//만약 밴된 도중에 다시 밴 된다면, 밴 시간만 조정한다.
	if(on_banned_)
	{
		GetWorld()->GetTimerManager().SetTimer(ban_time_handle_, FTimerDelegate::CreateWeakLambda(this, [this]()
		{
			passive_ref_->FinishHoldCoolDown();
			on_banned_ = false;
		}), duration, false);
		return;
	}

	//만약 패시브 스킬을 사용 중이거나, 실행 가능한 상태에서 ban이 걸리면, 패시브가 강제로 끝낸다.
	if(passive_ref_->IsOnPassiveSkill() || passive_ref_->IsPassiveAvailable())
	{
		passive_ref_->FinishPassiveSkillAndStartCoolDown();
	}
	
	//duration동안 쿨타임이 돌지 못하게 한다.
	passive_ref_->StartHoldCoolDown();
	GetWorld()->GetTimerManager().SetTimer(ban_time_handle_, FTimerDelegate::CreateWeakLambda(this, [this]()
			{
				passive_ref_->FinishHoldCoolDown();
				on_banned_ = false;
			}), duration, false);

	on_banned_ = true;
}

void UPassiveMechanics::ActivatePassiveSkill()
{
	passive_ref_->StartPassiveSkill();
}

void UPassiveMechanics::OnStunned()
{
	passive_ref_->StopPassiveSkill();
}

bool UPassiveMechanics::IsPassiveAvailable() const
{
	return passive_ref_->IsPassiveAvailable();
}

float UPassiveMechanics::GetHoldTime() const
{
	return passive_ref_->GetHoldTime();
}