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

#include "Managers/DataTableManager.h"
#include "Structs/WrapperEquipmentData.h"

void UEventManager::InitEventManager(TObjectPtr<UIKGameInstance> instance,
	TObjectPtr<UInventoryManager> inventory_manager)
{
	global_buff_subsystem_ = instance->GetSubsystem<UGlobalBuffSubsystem>();
	inventory_manager_ = inventory_manager;
}

FEventData UEventManager::GetRandomEventData()
{
	int32 rand_idx = FMath::RandRange(0, 7);
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
			return *event_table_->FindRow<FEventData>(FName("EMP"), TEXT(""));

		case 4:
			return *event_table_->FindRow<FEventData>(FName("Protocol:Survive"), TEXT(""));

		case 5:
			return *event_table_->FindRow<FEventData>(FName("Protocol:Assault"), TEXT(""));

		case 6:
			return *event_table_->FindRow<FEventData>(FName("Protocol:Efficiency"), TEXT(""));

		case 7:
			return *event_table_->FindRow<FEventData>(FName("AbandonedSupply"), TEXT(""));
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

	case EEventType::EMP:
		widget->button_1_->OnClicked.AddDynamic(this, &UEventManager::Event_EMP_FirstOptionResult);
		widget->button_2_->OnClicked.AddDynamic(this, &UEventManager::Event_EMP_SecondOptionResult);
		widget->button_3_->OnClicked.AddDynamic(this, &UEventManager::Event_EMP_ThirdOptionResult);
		break;

	case EEventType::ProtocolSurvive:
		widget->button_1_->OnClicked.AddDynamic(this, &UEventManager::Event_ProtocolSurvive_FirstOptionResult);
		widget->button_2_->OnClicked.AddDynamic(this, &UEventManager::Event_ProtocolSurvive_SecondOptionResult);
		widget->button_3_->OnClicked.AddDynamic(this, &UEventManager::Event_ProtocolSurvive_ThirdOptionResult);
		break;

	case EEventType::ProtocolAssault:
		widget->button_1_->OnClicked.AddDynamic(this, &UEventManager::Event_ProtocolAssault_FirstOptionResult);
		widget->button_2_->OnClicked.AddDynamic(this, &UEventManager::Event_ProtocolAssault_SecondOptionResult);
		widget->button_3_->OnClicked.AddDynamic(this, &UEventManager::Event_ProtocolAssault_ThirdOptionResult);
		break;

	case EEventType::ProtocolEfficiency:
		widget->button_1_->OnClicked.AddDynamic(this, &UEventManager::Event_ProtocolEfficiency_FirstOptionResult);
		widget->button_2_->OnClicked.AddDynamic(this, &UEventManager::Event_ProtocolEfficiency_SecondOptionResult);
		widget->button_3_->OnClicked.AddDynamic(this, &UEventManager::Event_ProtocolEfficiency_ThirdOptionResult);
		break;

	case EEventType::AbandonedSupply:
		widget->button_1_->OnClicked.AddDynamic(this, &UEventManager::Event_AbandonedSupply_FirstOptionResult);
		widget->button_2_->OnClicked.AddDynamic(this, &UEventManager::Event_AbandonedSupply_SecondOptionResult);
		widget->button_3_->OnClicked.AddDynamic(this, &UEventManager::Event_AbandonedSupply_ThirdOptionResult);
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
	for (auto& [Key, Value] : spawn_data)
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

void UEventManager::Event_EMP_FirstOptionResult()
{
	global_buff_subsystem_->AddBuff(EGlobalBuffType::EMP_CritBuff);
}

void UEventManager::Event_EMP_SecondOptionResult()
{
	global_buff_subsystem_->AddBuff(EGlobalBuffType::EMP_AttackSpeedBuff);
}

void UEventManager::Event_EMP_ThirdOptionResult()
{
	global_buff_subsystem_->AddBuff(EGlobalBuffType::EMP_HPDebuff);
}

void UEventManager::Event_ProtocolSurvive_FirstOptionResult()
{
	global_buff_subsystem_->AddBuff(EGlobalBuffType::ProtocolSurvive_Shield);
}

void UEventManager::Event_ProtocolSurvive_SecondOptionResult()
{
	global_buff_subsystem_->AddBuff(EGlobalBuffType::ProtocolSurvive_LifeSteal);
}

void UEventManager::Event_ProtocolSurvive_ThirdOptionResult()
{
	GetWorld()->GetGameInstance()->GetSubsystem<ULevelTransitionSubsystem>()->HealHeroesSpawnData(50);
}

void UEventManager::Event_ProtocolAssault_FirstOptionResult()
{
	global_buff_subsystem_->AddBuff(EGlobalBuffType::ProtocolAssault_AttackPowerBuff);
}

void UEventManager::Event_ProtocolAssault_SecondOptionResult()
{
	global_buff_subsystem_->AddBuff(EGlobalBuffType::ProtocolAssault_SkillPowerBuff);
}

void UEventManager::Event_ProtocolAssault_ThirdOptionResult()
{
	global_buff_subsystem_->AddBuff(EGlobalBuffType::ProtocolAssault_AttackSpeedBuff);
}

void UEventManager::Event_ProtocolEfficiency_FirstOptionResult()
{
	global_buff_subsystem_->AddBuff(EGlobalBuffType::ProtocolEfficiency_CritBuff);
}

void UEventManager::Event_ProtocolEfficiency_SecondOptionResult()
{
	global_buff_subsystem_->AddBuff(EGlobalBuffType::ProtocolEfficiency_EvadeBuff);
}

void UEventManager::Event_ProtocolEfficiency_ThirdOptionResult()
{
	global_buff_subsystem_->AddBuff(EGlobalBuffType::ProtocolEfficiency_CooldownBuff);
}

void UEventManager::Event_AbandonedSupply_FirstOptionResult()
{
	UWorld* world = GetWorld();
	if (!world)
	{
		return;
	}

	UIKGameInstance* instance = Cast<UIKGameInstance>(world->GetGameInstance());
	FWrapperEquipmentData data;
	data.active_skills_.Add(instance->GetDataTableManager()->GetActiveSkillDataByRarity(ERarity::Rare));
	inventory_manager_->OpenInventoryWidgetReward(data);
}

void UEventManager::Event_AbandonedSupply_SecondOptionResult()
{
	UWorld* world = GetWorld();
	if (!world)
	{
		return;
	}

	UIKGameInstance* instance = Cast<UIKGameInstance>(world->GetGameInstance());
	FWrapperEquipmentData data;
	data.passive_skills_ = instance->GetDataTableManager()->GetPassiveSkillDataByRarity(2, ERarity::Rare);
	inventory_manager_->OpenInventoryWidgetReward(data);
}

void UEventManager::Event_AbandonedSupply_ThirdOptionResult()
{
	UWorld* world = GetWorld();
	if (!world)
	{
		return;
	}

	UIKGameInstance* instance = Cast<UIKGameInstance>(world->GetGameInstance());
	FWrapperEquipmentData data;
	data.weapons_.Add(instance->GetDataTableManager()->GetWeaponDataByRarity(ERarity::Rare));
	inventory_manager_->OpenInventoryWidgetReward(data);
}
