/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 09.26.2024
Summary : Source file for skill containers.
					An actor component class to contain skills.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "Abilities/SkillContainer.h"

#include "Abilities/ActiveSkills/ActiveSkillBase.h"
#include "Characters/HeroBase.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/DataTableManager.h"
#include "WorldSettings/IKGameInstance.h"
#include "BrainComponent.h"

#include "Components/CharacterStatComponent.h"

// Sets default values for this component's properties
USkillContainer::USkillContainer()
	: Super::UActorComponent(), equipped_active_skill_data_(),data_table_cache_(nullptr), active_skill_(nullptr), hero_cache_(nullptr)
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	bWantsInitializeComponent = true;
}

void USkillContainer::BeginPlay()
{
	Super::BeginPlay();
	hero_cache_ = Cast<AHeroBase>(GetOwner());
	data_table_cache_ = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GetDataTableManager();
}

void USkillContainer::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	GetWorld()->GetTimerManager().ClearTimer(cool_down_handle_);
	GetWorld()->GetTimerManager().ClearTimer(casting_time_handle_);
	Super::EndPlay(EndPlayReason);
}

void USkillContainer::InitializeComponent()
{
	Super::InitializeComponent();
}

bool USkillContainer::HasActiveSkill() const
{
	return active_skill_ != nullptr;
}

float USkillContainer::GetCooltime() const
{
	if (active_skill_)
	{
		return active_skill_->GetCoolTime() * (100 / (100 + hero_cache_->GetCharacterStat()->GetSkillCooldown()));
	}
	return 0.f;
}

float USkillContainer::GetCastingTime() const
{
	if (active_skill_)
	{
		return active_skill_->GetCastingTime();
	}
	return 0.f;
}

bool USkillContainer::IsOnCoolDown() const
{
	return GetWorld()->GetTimerManager().IsTimerActive(cool_down_handle_);
}

float USkillContainer::GetLeftCoolDown() const
{
	if (IsOnCoolDown())
	{
		return GetWorld()->GetTimerManager().GetTimerRemaining(cool_down_handle_);
	}
	return 0.f;
}

void USkillContainer::ReduceCooltime(float reduce_time)
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

void USkillContainer::ReduceCooltimeByPercentage(float percentage)
{
	ReduceCooltime(GetCooltime() * percentage);
}

TOptional<FTargetParameters> USkillContainer::GetTargetParameters() const
{
	if (active_skill_)
	{
		return active_skill_->GetTargetParameters();
	}
	return NullOpt;
}

FActiveSkillData USkillContainer::GetEquippedActiveSkillData()
{
	return equipped_active_skill_data_;
}

USkillBase* USkillContainer::GetActiveSkill() const
{
	return active_skill_;
}

void USkillContainer::EquipActiveSkill(EActiveSkillType type)
{
	if (active_skill_)
	{
		UnEquipActiveSkill();
	}
	equipped_active_skill_data_ = data_table_cache_->GetActiveSkillData(type);
	active_skill_ = NewObject<UActiveSkillBase>(this, equipped_active_skill_data_.active_skill_class);
	active_skill_->InitActiveSkill(hero_cache_.Get());
}

void USkillContainer::UnEquipActiveSkill()
{
	equipped_active_skill_data_ = FActiveSkillData();
	active_skill_ = nullptr;
}

bool USkillContainer::ActivateSkill()
{
	if (active_skill_)
	{
		if (GetWorld()->GetTimerManager().IsTimerActive(cool_down_handle_) == false)
		{
			active_skill_->ActivateSkill();
			return true;
		}
	}
	return false;
}

void USkillContainer::DecideSkill(const FTargetResult& TargetResult)
{
	if (active_skill_)
	{
		active_skill_->Decide(TargetResult);
		GetWorld()->GetTimerManager().SetTimer(cool_down_handle_, GetCooltime(), false);
		FTimerDelegate cast_finish_delegate = FTimerDelegate::CreateUObject(this, &USkillContainer::OnCastingFinish);
		GetWorld()->GetTimerManager().SetTimer(casting_time_handle_, cast_finish_delegate, GetCastingTime(), false);
	}
}

void USkillContainer::OnCastingFinish()
{
	FAIMessage Msg(TEXT("CastingFinished"), this, active_skill_request_id_, FAIMessage::Success);
	FAIMessage::Send(Cast<APawn>(GetOwner()), Msg);
}

FAIRequestID USkillContainer::GetCastingRequestID() const
{
	return active_skill_request_id_;
}
