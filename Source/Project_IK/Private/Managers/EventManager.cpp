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
#include "UI/Map/IKMaps.h"
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

#include "DataAssets/EventDataAsset.h"

void UEventManager::InitEventManager(TObjectPtr<UIKGameInstance> instance,
	TObjectPtr<UInventoryManager> inventory_manager)
{
	global_buff_subsystem_ = instance->GetSubsystem<UGlobalBuffSubsystem>();
	inventory_manager_ = inventory_manager;
}

FEventData UEventManager::GetRandomEventData()
{
	return event_data_asset_->GetActiveSkillDataRandomly(IsNegativeEventsRemoved());
}

void UEventManager::BindEventResult(FEventData data, TObjectPtr<UEventWidget> widget)
{
	switch (data.event_type_)
	{
	case EEventType::AirStrike:
		widget->EnableButtons(3);
		widget->button_1_->OnClicked.AddDynamic(this, &UEventManager::Event_AirStrike_FirstOptionResult);
		widget->button_2_->OnClicked.AddDynamic(this, &UEventManager::Event_AirStrike_SecondOptionResult);
		widget->button_3_->OnClicked.AddDynamic(this, &UEventManager::Event_AirStrike_ThirdOptionResult);
		break;

	case EEventType::Ambush:
		widget->EnableButtons(3);
		widget->button_1_->OnClicked.AddDynamic(this, &UEventManager::Event_Ambush_FirstOptionResult);
		widget->button_2_->OnClicked.AddDynamic(this, &UEventManager::Event_Ambush_SecondOptionResult);
		widget->button_3_->OnClicked.AddDynamic(this, &UEventManager::Event_Ambush_ThirdOptionResult);
		break;

	case EEventType::Trap:
		widget->EnableButtons(3);
		widget->button_1_->OnClicked.AddDynamic(this, &UEventManager::Event_Trap_FirstOptionResult);
		widget->button_2_->OnClicked.AddDynamic(this, &UEventManager::Event_Trap_SecondOptionResult);
		widget->button_3_->OnClicked.AddDynamic(this, &UEventManager::Event_Trap_ThirdOptionResult);
		break;

	case EEventType::EMP:
		widget->EnableButtons(3);
		widget->button_1_->OnClicked.AddDynamic(this, &UEventManager::Event_EMP_FirstOptionResult);
		widget->button_2_->OnClicked.AddDynamic(this, &UEventManager::Event_EMP_SecondOptionResult);
		widget->button_3_->OnClicked.AddDynamic(this, &UEventManager::Event_EMP_ThirdOptionResult);
		break;

	case EEventType::ProtocolSurvive:
		widget->EnableButtons(3);
		widget->button_1_->OnClicked.AddDynamic(this, &UEventManager::Event_ProtocolSurvive_FirstOptionResult);
		widget->button_2_->OnClicked.AddDynamic(this, &UEventManager::Event_ProtocolSurvive_SecondOptionResult);
		widget->button_3_->OnClicked.AddDynamic(this, &UEventManager::Event_ProtocolSurvive_ThirdOptionResult);
		break;

	case EEventType::ProtocolAssault:
		widget->EnableButtons(3);
		widget->button_1_->OnClicked.AddDynamic(this, &UEventManager::Event_ProtocolAssault_FirstOptionResult);
		widget->button_2_->OnClicked.AddDynamic(this, &UEventManager::Event_ProtocolAssault_SecondOptionResult);
		widget->button_3_->OnClicked.AddDynamic(this, &UEventManager::Event_ProtocolAssault_ThirdOptionResult);
		break;

	case EEventType::ProtocolEfficiency:
		widget->EnableButtons(3);
		widget->button_1_->OnClicked.AddDynamic(this, &UEventManager::Event_ProtocolEfficiency_FirstOptionResult);
		widget->button_2_->OnClicked.AddDynamic(this, &UEventManager::Event_ProtocolEfficiency_SecondOptionResult);
		widget->button_3_->OnClicked.AddDynamic(this, &UEventManager::Event_ProtocolEfficiency_ThirdOptionResult);
		break;

	case EEventType::AbandonedSupply:
		widget->EnableButtons(3);
		widget->button_1_->OnClicked.AddDynamic(this, &UEventManager::Event_AbandonedSupply_FirstOptionResult);
		widget->button_2_->OnClicked.AddDynamic(this, &UEventManager::Event_AbandonedSupply_SecondOptionResult);
		widget->button_3_->OnClicked.AddDynamic(this, &UEventManager::Event_AbandonedSupply_ThirdOptionResult);
		break;

	case EEventType::Recon:
		widget->EnableButtons(3);
		widget->button_1_->OnClicked.AddDynamic(this, &UEventManager::Event_Recon_FirstOptionResult);
		widget->button_2_->OnClicked.AddDynamic(this, &UEventManager::Event_Recon_SecondOptionResult);
		widget->button_3_->OnClicked.AddDynamic(this, &UEventManager::Event_Recon_ThirdOptionResult);
		break;

	case EEventType::SetTrap:
		widget->EnableButtons(2);
		widget->button_1_->OnClicked.AddDynamic(this, &UEventManager::Event_SetTrap_FirstOptionResult);
		break;

	case EEventType::Core:
		widget->EnableButtons(2);
		widget->button_1_->OnClicked.AddDynamic(this, &UEventManager::Event_Core_FirstOptionResult);
		break;

	case EEventType::Patrol:
		widget->EnableButtons(4);
		widget->button_1_->OnClicked.AddDynamic(this, &UEventManager::Event_Patrol_FirstOptionResult);
		widget->button_2_->OnClicked.AddDynamic(this, &UEventManager::Event_Patrol_SecondOptionResult);
		widget->button_3_->OnClicked.AddDynamic(this, &UEventManager::Event_Patrol_ThirdOptionResult);
		widget->button_4_->OnClicked.AddDynamic(this, &UEventManager::Event_Patrol_FourthOptionResult);
		break;

	default:
		break;
	}
}

void UEventManager::CountUpIsNegativeEventsRemoved()
{
	++only_positive_event_counter_;
}

void UEventManager::CountDownIsNegativeEventsRemoved()
{
	--only_positive_event_counter_;
}

void UEventManager::Event_AirStrike_FirstOptionResult()
{
	// Discard a weapon randomly.
	ULevelTransitionSubsystem* subsystem = GetWorld()->GetGameInstance()->GetSubsystem<ULevelTransitionSubsystem>();
	auto spawn_data = subsystem->GetSpawnData();
	TArray<FWeaponData*> weapon_data_ref;
	for (auto& [Key, Value] : spawn_data)
	{
		if (Value.weapon_data_.type_ != EWeaponType::INVALID)
		{
			weapon_data_ref.Add(&Value.weapon_data_);
		}
	}

	if (!weapon_data_ref.IsEmpty())
	{
		int32 index = FMath::RandRange(0, weapon_data_ref.Num() - 1);
		*weapon_data_ref[index] = FWeaponData();
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
	TArray<FActiveSkillData*> active_data_ref;
	for (auto& [Key, Value] : spawn_data)
	{
		if (Value.active_skill_data_.type_ != EActiveSkillType::INVALID)
		{
			active_data_ref.Add(&Value.active_skill_data_);
		}
	}

	if (!active_data_ref.IsEmpty())
	{
		int32 index = FMath::RandRange(0, active_data_ref.Num() - 1);
		*active_data_ref[index] = FActiveSkillData();
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
	OpenInventory(data);
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
	OpenInventory(data);
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
	OpenInventory(data);
}

void UEventManager::Event_Recon_FirstOptionResult()
{
	CountUpIsNegativeEventsRemoved();
	global_buff_subsystem_->AddBuff(EGlobalBuffType::Recon_RemoveNegativeEvents);
}

void UEventManager::Event_Recon_SecondOptionResult()
{
	UPerkModifierSubsystem* perk_modifier = GetWorld()->GetGameInstance()->GetSubsystem<UPerkModifierSubsystem>();
	perk_modifier->SetCombatEndEquipmentRewardMaxChoice(
		perk_modifier->GetCombatEndEquipmentRewardMaxChoice() + 1
	);

	global_buff_subsystem_->AddBuff(EGlobalBuffType::Recon_RewardChoiceBuff);
}

void UEventManager::Event_Recon_ThirdOptionResult()
{
	UPerkModifierSubsystem* perk_modifier = GetWorld()->GetGameInstance()->GetSubsystem<UPerkModifierSubsystem>();
	perk_modifier->SetCombatEndCreditsBonusPercentage(
		perk_modifier->GetCombatEndCreditsBonusPercentage() + 0.2f
	);

	global_buff_subsystem_->AddBuff(EGlobalBuffType::Recon_CreditBonusBuff);
}

void UEventManager::Event_SetTrap_FirstOptionResult()
{
	bool is_succeed = FMath::RandBool();

	if (is_succeed)
	{
		global_buff_subsystem_->AddBuff(EGlobalBuffType::SetTrap_HPDebuff);
	}
	else
	{
		UIKGameInstance* instance = Cast<UIKGameInstance>(GetWorld()->GetGameInstance());
		UIKMaps* map = instance->GetMapPtr();
		TArray<FIntPoint> path = map->GetPlayerVisitedPath();
		if (path.IsEmpty())
		{
			for (int32 i = 0; i < map->GetWidth(); i++)
			{
				if (map->GetNode(0, i).type != NodeType::None)
				{
					SetNextNodeToElite(map, 0, i, 2);
				}
			}
		}
		else
		{
			FIntPoint position = path.Last();
			SetNextNodeToElite(map, position.X, position.Y, 2);
		}
	}
}

void UEventManager::Event_Core_FirstOptionResult()
{
	bool is_succeed = FMath::RandBool();

	if (is_succeed)
	{
		global_buff_subsystem_->AddBuff(EGlobalBuffType::Core_AttackBuff);
	}
	else
	{
		global_buff_subsystem_->AddBuff(EGlobalBuffType::Core_AttackDebuff);
	}
}

void UEventManager::Event_Patrol_FirstOptionResult()
{
	bool is_succeed = FMath::RandBool();

	if (is_succeed)
	{
		global_buff_subsystem_->AddBuff(EGlobalBuffType::Patrol_RandomBuff1);
	}
	else
	{
		global_buff_subsystem_->AddBuff(EGlobalBuffType::Patrol_RandomDebuff1);
	}
}

void UEventManager::Event_Patrol_SecondOptionResult()
{
	bool is_succeed = FMath::RandBool();

	if (is_succeed)
	{
		global_buff_subsystem_->AddBuff(EGlobalBuffType::Patrol_RandomBuff2);
	}
	else
	{
		global_buff_subsystem_->AddBuff(EGlobalBuffType::Patrol_RandomDebuff2);
	}
}

void UEventManager::Event_Patrol_ThirdOptionResult()
{

	bool is_succeed = FMath::RandBool();

	if (is_succeed)
	{
		global_buff_subsystem_->AddBuff(EGlobalBuffType::Patrol_RandomBuff3);
	}
	else
	{
		global_buff_subsystem_->AddBuff(EGlobalBuffType::Patrol_RandomDebuff3);
	}
}

void UEventManager::Event_Patrol_FourthOptionResult()
{

	bool is_succeed = FMath::RandBool();

	if (is_succeed)
	{
		global_buff_subsystem_->AddBuff(EGlobalBuffType::Patrol_RandomBuff4);
	}
	else
	{
		global_buff_subsystem_->AddBuff(EGlobalBuffType::Patrol_RandomDebuff4);
	}
}

void UEventManager::SetNextNodeToElite(UIKMaps* map, int32 row, int32 col, int32 left_level)
{
	if (left_level < 0)
	{
		return;
	}

	FMapNode node = map->GetNode(row, col);

	for (int32 next_index : node.next)
	{
		FMapNode next_node = map->GetNode(row + 1, next_index);
		next_node.type = NodeType::Enemy;
		map->SetNode(row + 1, next_index, next_node);
		SetNextNodeToElite(map, row + 1, next_index, left_level - 1);
	}
}

bool UEventManager::IsNegativeEventsRemoved() const
{
	return only_positive_event_counter_ > 0;
}

void UEventManager::OpenInventory(FWrapperEquipmentData data)
{
	inventory_manager_->OpenInventoryWidgetReward(data, [&]() {
		GetWorld()->GetGameInstance()->GetSubsystem<ULevelTransitionSubsystem>()->OpenMapLevel(GetWorld());
		});
}
