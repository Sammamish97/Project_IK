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

// Sets default values for this component's properties
USkillContainer::USkillContainer()
	: Super::UActorComponent()
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
	equip_manager_cache_ = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GetEquipManager();
}

void USkillContainer::InitializeComponent()
{
	Super::InitializeComponent();
}

FActiveSkillData USkillContainer::GetEquippedActiveSkillData()
{
	return equipped_active_skill_data_;
}

void USkillContainer::EquipActiveSkill(EActiveSkillType type)
{
	equipped_active_skill_data_ = equip_manager_cache_->GetActiveSkillData(type);
	active_skill_cache_ = NewObject<USkillBase>(this, equipped_active_skill_data_.active_skill_class);
	active_skill_cache_->InitActiveSkill(hero_cache_);
}

void USkillContainer::UnEquipActiveSkill()
{
	equipped_active_skill_data_ = equip_manager_cache_->GetActiveSkillData(EActiveSkillType::Empty);
	if(active_skill_cache_)
	{
		//UObject는 명시적으로 Destroy할 수 없다!
		//active_skill_cache_->Destroy();
	}
}

void USkillContainer::InvokeSkills(const FTargetResult& TargetResult)
{
	if (active_skill_cache_)
	{
		active_skill_cache_->ActivateSkill_Implementation(TargetResult);
	}
}
