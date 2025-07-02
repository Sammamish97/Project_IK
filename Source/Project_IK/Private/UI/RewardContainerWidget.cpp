/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.2.2025
Summary : Source file for Reward Container Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/RewardContainerWidget.h"

#include "Components/HorizontalBox.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/DataTableManager.h"
#include "UI/ActiveSkillSlotWidget.h"
#include "UI/PassiveSkillSlotWidget.h"
#include "UI/RuneSlotWidget.h"
#include "UI/WeaponSlotWidget.h"
#include "WorldSettings/IKGameInstance.h"

void URewardContainerWidget::LoadSelectedRewards(const FWrapperEquipmentData& rewards)
{
	reward_cache_ = rewards;
}

void URewardContainerWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//TEST perpose
	auto data_table_manager_ = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GetDataTableManager();
	// reward_cache_.active_skills_.Push(data_table_manager_->GetActiveSkillData(EActiveSkillType::ThunderStorm));
	// reward_cache_.active_skills_.Push(data_table_manager_->GetActiveSkillData(EActiveSkillType::ThunderStorm));
	//
	// reward_cache_.passive_skills_.Push(data_table_manager_->GetPassiveSkillData(EPassiveSkillType::Berserker));
	// reward_cache_.passive_skills_.Push(data_table_manager_->GetPassiveSkillData(EPassiveSkillType::Berserker));
	
	reward_cache_.runes_.Push(data_table_manager_->GetRuneData(ERuneSetType::Dagger, 0));
	reward_cache_.runes_.Push(data_table_manager_->GetRuneData(ERuneSetType::Dagger, 1));
	reward_cache_.runes_.Push(data_table_manager_->GetRuneData(ERuneSetType::Dagger, 2));
	reward_cache_.runes_.Push(data_table_manager_->GetRuneData(ERuneSetType::Dagger, 3));
	reward_cache_.runes_.Push(data_table_manager_->GetRuneData(ERuneSetType::Dagger, 4));
	reward_cache_.runes_.Push(data_table_manager_->GetRuneData(ERuneSetType::Dagger, 5));

	reward_cache_.runes_.Push(data_table_manager_->GetRuneData(ERuneSetType::Viper, 0));
	reward_cache_.runes_.Push(data_table_manager_->GetRuneData(ERuneSetType::Viper, 2));
	reward_cache_.runes_.Push(data_table_manager_->GetRuneData(ERuneSetType::Viper, 4));
	//
	
	for (auto weapon_data : reward_cache_.weapons_)
	{
		auto created_widget = CreateWidget<UWeaponSlotWidget>(this, weapon_slot_widget_class_);
		created_widget->SetWeaponSlotData(weapon_data);
		reward_slots_.Push(created_widget);
	}
	
	for (auto active_skill_data : reward_cache_.active_skills_)
	{
		auto created_widget = CreateWidget<UActiveSkillSlotWidget>(this, active_skill_slot_widget_class_);
		created_widget->SetActiveSkillSlotData(active_skill_data);
		reward_slots_.Push(created_widget);
	}
	
	for (auto passive_skill_data : reward_cache_.passive_skills_)
	{
		auto created_widget = CreateWidget<UPassiveSkillSlotWidget>(this, passive_skill_slot_widget_class_);
		created_widget->SetPassiveSkillSlotData(passive_skill_data);
		reward_slots_.Push(created_widget);
	}
	
	for (auto rune_data : reward_cache_.runes_)
    {
    	auto created_widget = CreateWidget<URuneSlotWidget>(this, rune_slot_widget_class_);
    	created_widget->SetRuneSetSlotData(rune_data);
    	reward_slots_.Push(created_widget);
    }

	for (auto elem : reward_slots_)
	{
		container_->AddChildToHorizontalBox(elem);
	}
}
