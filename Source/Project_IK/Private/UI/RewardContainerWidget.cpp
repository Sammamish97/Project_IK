/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.2.2025
Summary : Source file for Reward Container Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/RewardContainerWidget.h"

#include "Blueprint/DragDropOperation.h"
#include "Components/HorizontalBox.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/DataTableManager.h"
#include "UI/InventoryWidget.h"
#include "UI/InventorySlots/ActiveSkillSlotWidget.h"
#include "UI/InventorySlots/PassiveSkillSlotWidget.h"
#include "UI/InventorySlots/RuneSlotWidget.h"
#include "UI/InventorySlots/SupportSkillSlotWidget.h"
#include "UI/InventorySlots/WeaponSlotWidget.h"
#include "WorldSettings/IKGameInstance.h"

void URewardContainerWidget::SetInventoryWidgetCache(UInventoryWidget* widget_cache)
{
	inventory_widget_cache_ = widget_cache;
}

void URewardContainerWidget::LoadSelectedRewards(const FWrapperEquipmentData& rewards)
{
	reward_cache_ = rewards;
}

//이 함수의 목표는 add target을 그대로 reward slot에 추가하는것이 아니다.
//add_target의 type과 data만을 사용하여 새로운 widget을 생성 후, reward slot에 추가한다.
void URewardContainerWidget::AddToRewardContainer(UInventorySlot* add_target)
{
	switch (add_target->GetSlotType())
	{
		case EInventorySlotType::Weapon:
			{
				if (auto casted_from_weapon = Cast<UWeaponSlotWidget>(add_target))
				{
					auto created_widget = CreateWidget<UWeaponSlotWidget>(this, weapon_slot_widget_class_);
					created_widget->InitInventorySlot(inventory_widget_cache_, false);
					created_widget->SetWeaponSlotData(casted_from_weapon->GetStoredWeaponData());
					reward_slots_.Push(created_widget);
					container_->AddChildToHorizontalBox(created_widget);
				}
			}
			break;

		case EInventorySlotType::ActiveSkill:
			{
				if (auto casted_from_active_skill = Cast<UActiveSkillSlotWidget>(add_target))
				{
					auto created_widget = CreateWidget<UActiveSkillSlotWidget>(this, active_skill_slot_widget_class_);
					created_widget->InitInventorySlot(inventory_widget_cache_, false);
					created_widget->SetActiveSkillSlotData(casted_from_active_skill->GetStoredActiveSkillData());
					reward_slots_.Push(created_widget);
					container_->AddChildToHorizontalBox(created_widget);
				}
			}
			break;
			
		case EInventorySlotType::PassiveSkill:
			{
				if (auto casted_from_passive_skill = Cast<UPassiveSkillSlotWidget>(add_target))
				{
					auto created_widget = CreateWidget<UPassiveSkillSlotWidget>(this, passive_skill_slot_widget_class_);
					created_widget->InitInventorySlot(inventory_widget_cache_, false);
					created_widget->SetPassiveSkillSlotData(casted_from_passive_skill->GetStoredPassiveSkillData());
					reward_slots_.Push(created_widget);
					container_->AddChildToHorizontalBox(created_widget);
				}
			}
			break;

	case EInventorySlotType::SupportSkill:
		{
			if (auto casted_from_support_skill = Cast<USupportSkillSlotWidget>(add_target))
			{
				auto created_widget = CreateWidget<USupportSkillSlotWidget>(this, support_skill_slot_widget_class_);
				created_widget->InitInventorySlot(inventory_widget_cache_, false);
				created_widget->SetSupportSkillSlotData(casted_from_support_skill->GetStoredSupportSkillData());
				reward_slots_.Push(created_widget);
				container_->AddChildToHorizontalBox(created_widget);
			}
		}
		break;

		case EInventorySlotType::Rune_0:
		case EInventorySlotType::Rune_1:
		case EInventorySlotType::Rune_2:
		case EInventorySlotType::Rune_3:
		case EInventorySlotType::Rune_4:
		case EInventorySlotType::Rune_5:
			{
				if (auto casted_from_rune = Cast<URuneSlotWidget>(add_target))
				{
					auto created_widget = CreateWidget<URuneSlotWidget>(this, rune_slot_widget_class_);
					created_widget->InitInventorySlot(inventory_widget_cache_, false);
					created_widget->SetRuneSetSlotData(casted_from_rune->GetStoredRuneData());
					reward_slots_.Push(created_widget);
					container_->AddChildToHorizontalBox(created_widget);
					casted_from_rune->ClearData();
					inventory_widget_cache_->UpdateSetBonusEffect();
				}
			}
			break;
		default:
			break;
			
	}
}

void URewardContainerWidget::RemoveWidgetFromRewardContainer(UInventorySlot* remove_target)
{
	reward_slots_.Remove(remove_target);
	container_->ClearChildren();
	for (auto elem : reward_slots_)
	{
		container_->AddChildToHorizontalBox(elem);
	}
}

void URewardContainerWidget::NativeConstruct()
{
	Super::NativeConstruct();
	//TEST perpose
	auto data_table_manager_ = Cast<UIKGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GetDataTableManager();
	
	reward_cache_.active_skills_.Push(data_table_manager_->GetActiveSkillData(EActiveSkillType::ThunderStorm));
	reward_cache_.active_skills_.Push(data_table_manager_->GetActiveSkillData(EActiveSkillType::ThunderStorm));
	
	reward_cache_.passive_skills_.Push(data_table_manager_->GetPassiveSkillData(EPassiveSkillType::Berserker));
	reward_cache_.passive_skills_.Push(data_table_manager_->GetPassiveSkillData(EPassiveSkillType::LowProfile));
	reward_cache_.passive_skills_.Push(data_table_manager_->GetPassiveSkillData(EPassiveSkillType::Agility));

	reward_cache_.support_skills_.Push(data_table_manager_->GetSupportSkillData(ESupportSkillType::InstantRepair));
	reward_cache_.support_skills_.Push(data_table_manager_->GetSupportSkillData(ESupportSkillType::InstantRepair));

	reward_cache_.support_skills_.Push(data_table_manager_->GetSupportSkillData(ESupportSkillType::SupportFire));
	reward_cache_.support_skills_.Push(data_table_manager_->GetSupportSkillData(ESupportSkillType::SupportFire));

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

	for (auto support_skill_data : reward_cache_.support_skills_)
	{
		auto created_widget = CreateWidget<USupportSkillSlotWidget>(this, support_skill_slot_widget_class_);
		created_widget->SetSupportSkillSlotData(support_skill_data);
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
		elem->InitInventorySlot(inventory_widget_cache_, false);
		container_->AddChildToHorizontalBox(elem);
	}
}

bool URewardContainerWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	if (auto casted_from = Cast<UInventorySlot>(InOperation->Payload))
	{
		//1. 만약 이미 Reward내부에 있는 widget이라면 Drop을 취소.
		if (reward_slots_.Contains(casted_from))
		{
			return false;
		}
		
		//2. 만약 Board에서 오는 Widget이라면 생성 후 board를 clear
		AddToRewardContainer(casted_from);
		casted_from->ClearData();
	}
	return false;
}
