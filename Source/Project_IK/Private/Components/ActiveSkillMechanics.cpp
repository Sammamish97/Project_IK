/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.26.2024
Summary : Source file for skill containers.
					An actor component class to contain skills.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Components/ActiveSkillMechanics.h"

#include "Abilities/SkillBase.h"
#include "Characters/HeroBase.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/DataTableManager.h"
#include "WorldSettings/IKGameInstance.h"
#include "BrainComponent.h"

#include "Components/CharacterStatComponent.h"

// Sets default values for this component's properties
UActiveSkillMechanics::UActiveSkillMechanics()
	: Super::UActorComponent(), equipped_active_skill_data_(),data_table_cache_(nullptr), active_skill_(nullptr), hero_cache_(nullptr)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	bWantsInitializeComponent = true;
}

void UActiveSkillMechanics::BeginPlay()
{
	Super::BeginPlay();
	hero_cache_ = Cast<AHeroBase>(GetOwner());
	data_table_cache_ = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GetDataTableManager();
}

void UActiveSkillMechanics::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearTimer(cool_down_handle_);
	GetWorld()->GetTimerManager().ClearTimer(casting_time_handle_);
	Super::EndPlay(EndPlayReason);
}

void UActiveSkillMechanics::InitializeComponent()
{
	Super::InitializeComponent();
}
TOptional<FTargetParameters> UActiveSkillMechanics::GetTargetParameters() const
{
	if (active_skill_)
	{
		return active_skill_->GetTargetParameters();
	}
	return NullOpt;
}

bool UActiveSkillMechanics::HasActiveSkill() const
{
	return active_skill_ != nullptr;
}

float UActiveSkillMechanics::GetCooltime() const
{
	if (active_skill_)
	{
		return active_skill_->GetCoolTime() * (100 / (100 + hero_cache_->GetCharacterStat()->GetSkillCooldown()));
	}
	return 0.f;
}

float UActiveSkillMechanics::GetCastingTime() const
{
	if (active_skill_)
	{
		return active_skill_->GetCastingTime();
	}
	return 0.f;
}

bool UActiveSkillMechanics::IsOnCoolDown() const
{
	return GetWorld()->GetTimerManager().IsTimerActive(cool_down_handle_);
}

float UActiveSkillMechanics::GetLeftCoolDown() const
{
	if (IsOnCoolDown())
	{
		return GetWorld()->GetTimerManager().GetTimerRemaining(cool_down_handle_);
	}
	return 0.f;
}

void UActiveSkillMechanics::ReduceCooltime(float reduce_time)
{
	float remain_time = GetLeftCoolDown();

	if (remain_time > 0.f)
	{
		GetWorld()->GetTimerManager().ClearTimer(cool_down_handle_);

		float reduced_time = remain_time - reduce_time;

		if (reduced_time > 0.f)
		{
			GetWorld()->GetTimerManager().SetTimer(cool_down_handle_, reduced_time, false);
		}
	}
}

void UActiveSkillMechanics::ReduceCooltimeByPercentage(float percentage)
{
	ReduceCooltime(GetCooltime() * percentage);
}

FActiveSkillData UActiveSkillMechanics::GetEquippedActiveSkillData()
{
	return equipped_active_skill_data_;
}

void UActiveSkillMechanics::EquipActiveSkill(EActiveSkillType type)
{
	if (active_skill_)
	{
		UnEquipActiveSkill();
	}
	equipped_active_skill_data_ = data_table_cache_->GetActiveSkillData(type);
	active_skill_ = NewObject<USkillBase>(this, equipped_active_skill_data_.active_skill_class);
	active_skill_->InitActiveSkill(hero_cache_.Get());
}

void UActiveSkillMechanics::UnEquipActiveSkill()
{
	equipped_active_skill_data_ = FActiveSkillData();
	active_skill_ = nullptr;
}

bool UActiveSkillMechanics::InvokeSkills(const FTargetResult& TargetResult)
{
	if (active_skill_)
	{
		if (GetWorld()->GetTimerManager().IsTimerActive(cool_down_handle_) == false)
		{
			active_skill_->ActivateSkill(TargetResult);
			on_active_skill_.Broadcast(GetCooltime());
			
			GetWorld()->GetTimerManager().SetTimer(cool_down_handle_, GetCooltime(), false);

			FTimerDelegate cast_finish_delegate = FTimerDelegate::CreateUObject(this, &UActiveSkillMechanics::OnCastingFinish);
			GetWorld()->GetTimerManager().SetTimer(casting_time_handle_, cast_finish_delegate, GetCastingTime(), false);
			return true;
		}
	}
	return false;
}

void UActiveSkillMechanics::OnCastingFinish()
{
	FAIMessage Msg(TEXT("CastingFinished"), this, active_skill_request_id_, FAIMessage::Success);
	FAIMessage::Send(Cast<APawn>(GetOwner()), Msg);
}

FAIRequestID UActiveSkillMechanics::GetCastingRequestID() const
{
	return active_skill_request_id_;
}
