/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 04.04.2025
Summary : Source file for Event Manager

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "EventManager.h"
#include "Managers/EventManager.h"
#include "Managers/InventoryManager.h"
#include "Subsystems/GlobalBuffSubsystem.h"
#include "Subsystems/LevelTransitionSubsystem.h"
#include "Subsystems/PerkModifierSubsystem.h"

#include "Components/Button.h"
#include "Managers/EnumCluster.h"
#include "Structs/EventData.h"
#include "UI/EventWidget.h"
#include "WorldSettings/IKGameInstance.h"

#include "Subsystems/GlobalBuffSubsystem.h"

void UEventManager::InitEventManager(TObjectPtr<UIKGameInstance> instance,
	TObjectPtr<UInventoryManager> inventory_manager)
{
	global_buff_subsystem_ = instance->GetSubsystem<UGlobalBuffSubsystem>();
	inventory_manager_ = inventory_manager;
}

FEventData UEventManager::GetRandomEventData()
{
	int32 rand_idx = FMath::RandRange(0, 3);
	if (event_table_)
	{
		switch (rand_idx)
		{
			case 0:
				return *event_table_->FindRow<FEventData>(FName("AirStrike"), TEXT(""));
			
			case 1:
				return *event_table_->FindRow<FEventData>(FName("Ambush"), TEXT(""));
			
			case 2:
				return *event_table_->FindRow<FEventData>(FName("Trap"), TEXT(""));
			
			case 3:
				return *event_table_->FindRow<FEventData>(FName("EventType_4"), TEXT(""));
		}
	}
	return FEventData();
}

void UEventManager::BindEventResult(FEventData data, TObjectPtr<UEventWidget> widget)
{
	switch (data.event_type_)
	{
	case EEventType::AirStrike:
		widget->button_1_->OnClicked.AddDynamic(this, &UEventManager::Event_AirStrike_FirstOptionResult);
		widget->button_2_->OnClicked.AddDynamic(this, &UEventManager::Event_AirStrike_SecondOptionResult);
		widget->button_3_->OnClicked.AddDynamic(this, &UEventManager::Event_AirStrike_ThirdOptionResult);
		break;

	case EEventType::Ambush:
		widget->button_1_->OnClicked.AddDynamic(this, &UEventManager::Event_Ambush_FirstOptionResult);
		widget->button_2_->OnClicked.AddDynamic(this, &UEventManager::Event_Ambush_SecondOptionResult);
		widget->button_3_->OnClicked.AddDynamic(this, &UEventManager::Event_Ambush_ThirdOptionResult);
		break;

	case EEventType::Trap:
		widget->button_1_->OnClicked.AddDynamic(this, &UEventManager::Event_Trap_FirstOptionResult);
		widget->button_2_->OnClicked.AddDynamic(this, &UEventManager::Event_Trap_SecondOptionResult);
		widget->button_3_->OnClicked.AddDynamic(this, &UEventManager::Event_Trap_ThirdOptionResult);
		break;

	case EEventType::EventType_4:
		widget->button_1_->OnClicked.AddDynamic(this, &UEventManager::Event_4_FirstOptionResult);
		widget->button_2_->OnClicked.AddDynamic(this, &UEventManager::Event_4_SecondOptionResult);
		widget->button_3_->OnClicked.AddDynamic(this, &UEventManager::Event_4_ThirdOptionResult);
		break;

	default:
		break;
	}
}

void UEventManager::Event_AirStrike_FirstOptionResult()
{
	// Discard a weapon randomly.
	ULevelTransitionSubsystem* subsystem = GetWorld()->GetGameInstance()->GetSubsystem<ULevelTransitionSubsystem>();
	auto spawn_data = subsystem->GetSpawnData();
	TArray<TOptional<FWeaponData>*> weapon_data_ref;
	for (auto& [Key,Value] : spawn_data)
	{
		if (Value.weapon_data_.IsSet())
		{
			weapon_data_ref.Add(&Value.weapon_data_);
		}
	}

	if (!weapon_data_ref.IsEmpty())
	{
		int32 index = FMath::RandRange(0, weapon_data_ref.Num() - 1);
		weapon_data_ref[index]->Reset();
	}
}

void UEventManager::Event_AirStrike_SecondOptionResult()
{
	UGlobalBuffSubsystem* subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UGlobalBuffSubsystem>();
	subsystem->AddBuff(EGlobalBuffType::AirStrike_HPDebuff);
}

void UEventManager::Event_AirStrike_ThirdOptionResult()
{
	UGlobalBuffSubsystem* subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UGlobalBuffSubsystem>();
	subsystem->AddBuff(EGlobalBuffType::AirStrike_ArmorDebuff);
}

//Event 2: 장비
void UEventManager::Event_Ambush_FirstOptionResult()
{
	// Discard a active skill randomly.
	ULevelTransitionSubsystem* subsystem = GetWorld()->GetGameInstance()->GetSubsystem<ULevelTransitionSubsystem>();
	auto spawn_data = subsystem->GetSpawnData();
	TArray<TOptional<FActiveSkillData>*> active_data_ref;
	for (auto& [Key, Value] : spawn_data)
	{
		if (Value.active_skill_data_.IsSet())
		{
			active_data_ref.Add(&Value.active_skill_data_);
		}
	}

	if (!active_data_ref.IsEmpty())
	{
		int32 index = FMath::RandRange(0, active_data_ref.Num() - 1);
		active_data_ref[index]->Reset();
	}
}

void UEventManager::Event_Ambush_SecondOptionResult()
{
	UGlobalBuffSubsystem* subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UGlobalBuffSubsystem>();
	subsystem->AddBuff(EGlobalBuffType::Ambush_AttackSpeedDebuff);
}

void UEventManager::Event_Ambush_ThirdOptionResult()
{
	UGlobalBuffSubsystem* subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UGlobalBuffSubsystem>();
	subsystem->AddBuff(EGlobalBuffType::Ambush_AttackPowerDebuff);
}

//Event 3: 룬
void UEventManager::Event_Trap_FirstOptionResult()
{
	inventory_manager_->SetCredits(
		FMath::Max(inventory_manager_->GetCredits() - 200, 0)
	);
}

void UEventManager::Event_Trap_SecondOptionResult()
{

	UPerkModifierSubsystem* perk_modifier = GetWorld()->GetGameInstance()->GetSubsystem<UPerkModifierSubsystem>();
	perk_modifier->SetCombatEndEquipmentRewardNumCandidates(
		FMath::Max(perk_modifier->GetCombatEndEquipmentRewardNumCandidates() - 2, 0)
	);

	UGlobalBuffSubsystem* subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UGlobalBuffSubsystem>();
	subsystem->AddBuff(EGlobalBuffType::Trap_RewardCandidateDebuff);
}

void UEventManager::Event_Trap_ThirdOptionResult()
{

	UPerkModifierSubsystem* perk_modifier = GetWorld()->GetGameInstance()->GetSubsystem<UPerkModifierSubsystem>();
	perk_modifier->SetCombatEndEquipmentRewardMaxChoice(
		FMath::Max(perk_modifier->GetCombatEndEquipmentRewardMaxChoice() - 1, 0)
	);

	UGlobalBuffSubsystem* subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UGlobalBuffSubsystem>();
	subsystem->AddBuff(EGlobalBuffType::Trap_RewardChoiceDebuff);
}

//Event 4: 글로벌 버프

void UEventManager::Event_4_FirstOptionResult()
{
	global_buff_subsystem_->AddBuff(EGlobalBuffType::WoundingBullets);
}

void UEventManager::Event_4_SecondOptionResult()
{
	global_buff_subsystem_->AddBuff(EGlobalBuffType::WoundingBullets);
}

void UEventManager::Event_4_ThirdOptionResult()
{
	global_buff_subsystem_->AddBuff(EGlobalBuffType::WoundingBullets);
}
