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

#include "Abilities/SkillBase.h"
#include "Characters/HeroBase.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/DataTableManager.h"
#include "WorldSettings/IKGameInstance.h"

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

void USkillContainer::InitializeComponent()
{
	Super::InitializeComponent();
}
TOptional<FTargetParameters> USkillContainer::GetTargetParameters() const
{
	if (active_skill_)
	{
		return active_skill_->GetTargetParameters();
	}
	return NullOpt;
}

float USkillContainer::GetCooltime() const
{
	if (active_skill_)
	{
		return active_skill_->GetCooltime() * (100 / (100 + hero_cache_->GetCharacterStat()->GetSkillCooldown()));
	}
	return 0.f;
}

FActiveSkillData USkillContainer::GetEquippedActiveSkillData()
{
	return equipped_active_skill_data_;
}

void USkillContainer::EquipActiveSkill(EActiveSkillType type)
{
	if (active_skill_)
	{
		UnEquipActiveSkill();
	}
	equipped_active_skill_data_ = data_table_cache_->GetActiveSkillData(type);
	active_skill_ = NewObject<USkillBase>(this, equipped_active_skill_data_.active_skill_class);
	active_skill_->InitActiveSkill(hero_cache_.Get());
}

void USkillContainer::UnEquipActiveSkill()
{
	equipped_active_skill_data_ = data_table_cache_->GetActiveSkillData(EActiveSkillType::Empty);
	if(active_skill_)
	{
		active_skill_ = nullptr;
	}
}

void USkillContainer::InvokeSkills(const FTargetResult& TargetResult)
{
	if (active_skill_)
	{
		active_skill_->ActivateSkill(TargetResult);
	}
}
