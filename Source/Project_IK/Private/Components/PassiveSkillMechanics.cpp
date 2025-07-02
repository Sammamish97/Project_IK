/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.09.2025
Summary : Source file for Passive Skill Mechanics.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "Components/PassiveSkillMechanics.h"

#include "Abilities/PassiveSkills/PassiveSkillBase.h"
#include "Characters/HeroBase.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/DataTableManager.h"
#include "WorldSettings/IKGameInstance.h"

void UPassiveSkillMechanics::BeginPlay()
{
	Super::BeginPlay();
	hero_cache_ = Cast<AHeroBase>(GetOwner());
	data_table_cache_ = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GetDataTableManager();
}

FPassiveSkillData UPassiveSkillMechanics::GetEquippedPassiveSkillData()
{
	return equipped_passive_skill_data_;
}

void UPassiveSkillMechanics::EquipPassiveSkill(EPassiveSkillType type)
{
	equipped_passive_skill_data_ = data_table_cache_->GetPassiveSkillData(type);
	passive_skill_cache_ = NewObject<UPassiveSkillBase>(this, equipped_passive_skill_data_.passive_skill_class);
}

//Equip의 생성 시점과 Init시점을 분리 시킨 이유는, Init시점에서 바로 발동이 되는 패시브 스킬(ex: LowProfile)은 HUD가 생성되기 전에 AddBuff가 적용되어
//HUD에 UI가 정상적으로 추가되지 않는다.
//해당 이슈를 해결하기 위해 Passive Skill의 Init은 따로 분리하여, GameMode의 StartPlay에서 호출해준다.
void UPassiveSkillMechanics::InitPassiveSkill()
{
	if (passive_skill_cache_)
	{
		passive_skill_cache_->InitEquipmentSkill(hero_cache_);
	}
}

void UPassiveSkillMechanics::UnEquipPassiveSkill()
{
	equipped_passive_skill_data_ = data_table_cache_->GetPassiveSkillData(EPassiveSkillType::INVALID);
}