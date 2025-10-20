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

#include "Subsystems/RandomNumberGeneratorSubsystem.h"

void UEventManager::InitEventManager(TObjectPtr<class UIKGameInstance> instance,
	TObjectPtr<class UInventoryManager> inventory_manager, TObjectPtr<class UTextManager> text_manager)
{
	global_buff_subsystem_ = instance->GetSubsystem<UGlobalBuffSubsystem>();
	inventory_manager_ = inventory_manager;
	text_manager_cache_ = text_manager;
}

FEventData UEventManager::GetRandomEventData()
{
	return event_data_asset_->GetActiveSkillDataRandomly(GetWorld(), IsNegativeEventsRemoved());
}

void UEventManager::BindEventResult(FEventData data, TObjectPtr<UEventWidget> widget)
{
	event_widget_cache_ = widget;
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
		int32 index = URandomNumberGeneratorSubsystem::GetRNG(GetWorld()).RandRange(0, weapon_data_ref.Num() - 1);
		*weapon_data_ref[index] = FWeaponData();

		FText base = text_manager_cache_->GetEventResultText(EEventType::AirStrike, 0);
		FFormatNamedArguments args;
		args.Add("NAME", text_manager_cache_->GetHeroNameText(IntToHeroType(index)));
		
		event_widget_cache_->UpdateTextBody(FText::Format(base, args));
	}
}


void UEventManager::Event_AirStrike_SecondOptionResult()
{
	UGlobalBuffSubsystem* subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UGlobalBuffSubsystem>();
	subsystem->AddBuff(EGlobalBuffType::AirStrike_HPDebuff);
	event_widget_cache_->UpdateTextBody(text_manager_cache_->GetEventResultText(EEventType::AirStrike, 1));
}

void UEventManager::Event_AirStrike_ThirdOptionResult()
{
	UGlobalBuffSubsystem* subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UGlobalBuffSubsystem>();
	subsystem->AddBuff(EGlobalBuffType::AirStrike_ArmorDebuff);
	event_widget_cache_->UpdateTextBody(text_manager_cache_->GetEventResultText(EEventType::AirStrike, 2));
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
		int32 index = URandomNumberGeneratorSubsystem::GetRNG(GetWorld()).RandRange(0, active_data_ref.Num() - 1);
		*active_data_ref[index] = FActiveSkillData();

		FText base = text_manager_cache_->GetEventResultText(EEventType::Ambush, 0);
		FFormatNamedArguments args;
		args.Add("NAME", text_manager_cache_->GetHeroNameText(IntToHeroType(index)));
		
		event_widget_cache_->UpdateTextBody(FText::Format(base, args));
	}
}

void UEventManager::Event_Ambush_SecondOptionResult()
{
	UGlobalBuffSubsystem* subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UGlobalBuffSubsystem>();
	subsystem->AddBuff(EGlobalBuffType::Ambush_AttackSpeedDebuff);
	event_widget_cache_->UpdateTextBody(text_manager_cache_->GetEventResultText(EEventType::Ambush, 1));
}

void UEventManager::Event_Ambush_ThirdOptionResult()
{
	UGlobalBuffSubsystem* subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UGlobalBuffSubsystem>();
	subsystem->AddBuff(EGlobalBuffType::Ambush_AttackPowerDebuff);
	event_widget_cache_->UpdateTextBody(text_manager_cache_->GetEventResultText(EEventType::Ambush, 2));
}

void UEventManager::Event_Trap_FirstOptionResult()
{
	inventory_manager_->SetCredits(
		FMath::Max(inventory_manager_->GetCredits() - 200, 0)
	);

	event_widget_cache_->UpdateTextBody(text_manager_cache_->GetEventResultText(EEventType::Trap, 0));
}

void UEventManager::Event_Trap_SecondOptionResult()
{

	UPerkModifierSubsystem* perk_modifier = GetWorld()->GetGameInstance()->GetSubsystem<UPerkModifierSubsystem>();
	perk_modifier->SetCombatEndEquipmentRewardNumCandidates(
		FMath::Max(perk_modifier->GetCombatEndEquipmentRewardNumCandidates() - 2, 0)
	);

	UGlobalBuffSubsystem* subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UGlobalBuffSubsystem>();
	subsystem->AddBuff(EGlobalBuffType::Trap_RewardCandidateDebuff);
	event_widget_cache_->UpdateTextBody(text_manager_cache_->GetEventResultText(EEventType::Trap, 1));
}

void UEventManager::Event_Trap_ThirdOptionResult()
{

	UPerkModifierSubsystem* perk_modifier = GetWorld()->GetGameInstance()->GetSubsystem<UPerkModifierSubsystem>();
	perk_modifier->SetCombatEndEquipmentRewardMaxChoice(
		FMath::Max(perk_modifier->GetCombatEndEquipmentRewardMaxChoice() - 1, 0)
	);

	UGlobalBuffSubsystem* subsystem = GetWorld()->GetGameInstance()->GetSubsystem<UGlobalBuffSubsystem>();
	subsystem->AddBuff(EGlobalBuffType::Trap_RewardChoiceDebuff);
	event_widget_cache_->UpdateTextBody(text_manager_cache_->GetEventResultText(EEventType::Trap, 2));
}

void UEventManager::Event_EMP_FirstOptionResult()
{
	global_buff_subsystem_->AddBuff(EGlobalBuffType::EMP_CritBuff);
	event_widget_cache_->UpdateTextBody(text_manager_cache_->GetEventResultText(EEventType::EMP, 0));
}

void UEventManager::Event_EMP_SecondOptionResult()
{
	global_buff_subsystem_->AddBuff(EGlobalBuffType::EMP_AttackSpeedBuff);
	event_widget_cache_->UpdateTextBody(text_manager_cache_->GetEventResultText(EEventType::EMP, 1));
}

void UEventManager::Event_EMP_ThirdOptionResult()
{
	global_buff_subsystem_->AddBuff(EGlobalBuffType::EMP_HPDebuff);
	event_widget_cache_->UpdateTextBody(text_manager_cache_->GetEventResultText(EEventType::EMP, 2));
}

void UEventManager::Event_ProtocolSurvive_FirstOptionResult()
{
	global_buff_subsystem_->AddBuff(EGlobalBuffType::ProtocolSurvive_Shield);
	event_widget_cache_->UpdateTextBody(text_manager_cache_->GetEventResultText(EEventType::ProtocolSurvive, 0));
}

void UEventManager::Event_ProtocolSurvive_SecondOptionResult()
{
	global_buff_subsystem_->AddBuff(EGlobalBuffType::ProtocolSurvive_LifeSteal);
	event_widget_cache_->UpdateTextBody(text_manager_cache_->GetEventResultText(EEventType::ProtocolSurvive, 1));
}

void UEventManager::Event_ProtocolSurvive_ThirdOptionResult()
{
	GetWorld()->GetGameInstance()->GetSubsystem<ULevelTransitionSubsystem>()->HealHeroesSpawnData(50);
	event_widget_cache_->UpdateTextBody(text_manager_cache_->GetEventResultText(EEventType::ProtocolSurvive, 2));
}

void UEventManager::Event_ProtocolAssault_FirstOptionResult()
{
	global_buff_subsystem_->AddBuff(EGlobalBuffType::ProtocolAssault_AttackPowerBuff);
	event_widget_cache_->UpdateTextBody(text_manager_cache_->GetEventResultText(EEventType::ProtocolAssault, 0));
}

void UEventManager::Event_ProtocolAssault_SecondOptionResult()
{
	global_buff_subsystem_->AddBuff(EGlobalBuffType::ProtocolAssault_SkillPowerBuff);
	event_widget_cache_->UpdateTextBody(text_manager_cache_->GetEventResultText(EEventType::ProtocolAssault, 1));
}

void UEventManager::Event_ProtocolAssault_ThirdOptionResult()
{
	global_buff_subsystem_->AddBuff(EGlobalBuffType::ProtocolAssault_AttackSpeedBuff);
	event_widget_cache_->UpdateTextBody(text_manager_cache_->GetEventResultText(EEventType::ProtocolAssault, 2));
}

void UEventManager::Event_ProtocolEfficiency_FirstOptionResult()
{
	global_buff_subsystem_->AddBuff(EGlobalBuffType::ProtocolEfficiency_CritBuff);
	event_widget_cache_->UpdateTextBody(text_manager_cache_->GetEventResultText(EEventType::ProtocolEfficiency, 0));
}

void UEventManager::Event_ProtocolEfficiency_SecondOptionResult()
{
	global_buff_subsystem_->AddBuff(EGlobalBuffType::ProtocolEfficiency_EvadeBuff);
	event_widget_cache_->UpdateTextBody(text_manager_cache_->GetEventResultText(EEventType::ProtocolEfficiency, 1));
}

void UEventManager::Event_ProtocolEfficiency_ThirdOptionResult()
{
	global_buff_subsystem_->AddBuff(EGlobalBuffType::ProtocolEfficiency_CooldownBuff);
	event_widget_cache_->UpdateTextBody(text_manager_cache_->GetEventResultText(EEventType::ProtocolEfficiency, 2));
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
	event_widget_cache_->UpdateTextBody(text_manager_cache_->GetEventResultText(EEventType::AbandonedSupply, 0));
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
	event_widget_cache_->UpdateTextBody(text_manager_cache_->GetEventResultText(EEventType::AbandonedSupply, 1));
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
	event_widget_cache_->UpdateTextBody(text_manager_cache_->GetEventResultText(EEventType::AbandonedSupply, 2));
}

void UEventManager::Event_Recon_FirstOptionResult()
{
	CountUpIsNegativeEventsRemoved();
	global_buff_subsystem_->AddBuff(EGlobalBuffType::Recon_RemoveNegativeEvents);
	event_widget_cache_->UpdateTextBody(text_manager_cache_->GetEventResultText(EEventType::Recon, 0));
}

void UEventManager::Event_Recon_SecondOptionResult()
{
	UPerkModifierSubsystem* perk_modifier = GetWorld()->GetGameInstance()->GetSubsystem<UPerkModifierSubsystem>();
	perk_modifier->SetCombatEndEquipmentRewardMaxChoice(
		perk_modifier->GetCombatEndEquipmentRewardMaxChoice() + 1
	);

	global_buff_subsystem_->AddBuff(EGlobalBuffType::Recon_RewardChoiceBuff);
	event_widget_cache_->UpdateTextBody(text_manager_cache_->GetEventResultText(EEventType::Recon, 1));
}

void UEventManager::Event_Recon_ThirdOptionResult()
{
	UPerkModifierSubsystem* perk_modifier = GetWorld()->GetGameInstance()->GetSubsystem<UPerkModifierSubsystem>();
	perk_modifier->SetCombatEndCreditsBonusPercentage(
		perk_modifier->GetCombatEndCreditsBonusPercentage() + 0.2f
	);

	global_buff_subsystem_->AddBuff(EGlobalBuffType::Recon_CreditBonusBuff);
	event_widget_cache_->UpdateTextBody(text_manager_cache_->GetEventResultText(EEventType::Recon, 2));
}

void UEventManager::Event_SetTrap_FirstOptionResult()
{
	bool is_succeed = URandomNumberGeneratorSubsystem::Get(GetWorld())->RandBool();

	if (is_succeed)
	{
		global_buff_subsystem_->AddBuff(EGlobalBuffType::SetTrap_HPDebuff);
		event_widget_cache_->UpdateTextBody(text_manager_cache_->GetEventResultText(EEventType::SetTrap, 0));
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
		event_widget_cache_->UpdateTextBody(text_manager_cache_->GetEventResultText(EEventType::SetTrap, 1));
	}
}

void UEventManager::Event_Core_FirstOptionResult()
{
	bool is_succeed = URandomNumberGeneratorSubsystem::Get(GetWorld())->RandBool();

	if (is_succeed)
	{
		global_buff_subsystem_->AddBuff(EGlobalBuffType::Core_AttackBuff);
		event_widget_cache_->UpdateTextBody(text_manager_cache_->GetEventResultText(EEventType::Core, 0));
	}
	else
	{
		global_buff_subsystem_->AddBuff(EGlobalBuffType::Core_AttackDebuff);
		event_widget_cache_->UpdateTextBody(text_manager_cache_->GetEventResultText(EEventType::Core, 1));
	}
}

void UEventManager::Event_Patrol_FirstOptionResult()
{
	bool is_succeed = URandomNumberGeneratorSubsystem::Get(GetWorld())->RandBool();

	if (is_succeed)
	{
		global_buff_subsystem_->AddBuff(EGlobalBuffType::Patrol_RandomBuff1);
		event_widget_cache_->UpdateTextBody(text_manager_cache_->GetEventResultText(EEventType::Patrol, 0));
	}
	else
	{
		global_buff_subsystem_->AddBuff(EGlobalBuffType::Patrol_RandomDebuff1);
		event_widget_cache_->UpdateTextBody(text_manager_cache_->GetEventResultText(EEventType::Patrol, 1));
	}
}

void UEventManager::Event_Patrol_SecondOptionResult()
{
	bool is_succeed = URandomNumberGeneratorSubsystem::Get(GetWorld())->RandBool();

	if (is_succeed)
	{
		global_buff_subsystem_->AddBuff(EGlobalBuffType::Patrol_RandomBuff2);
		event_widget_cache_->UpdateTextBody(text_manager_cache_->GetEventResultText(EEventType::Patrol, 0));
	}
	else
	{
		global_buff_subsystem_->AddBuff(EGlobalBuffType::Patrol_RandomDebuff2);
		event_widget_cache_->UpdateTextBody(text_manager_cache_->GetEventResultText(EEventType::Patrol, 1));
	}
}

void UEventManager::Event_Patrol_ThirdOptionResult()
{

	bool is_succeed = URandomNumberGeneratorSubsystem::Get(GetWorld())->RandBool();

	if (is_succeed)
	{
		global_buff_subsystem_->AddBuff(EGlobalBuffType::Patrol_RandomBuff3);
		event_widget_cache_->UpdateTextBody(text_manager_cache_->GetEventResultText(EEventType::Patrol, 0));
	}
	else
	{
		global_buff_subsystem_->AddBuff(EGlobalBuffType::Patrol_RandomDebuff3);
		event_widget_cache_->UpdateTextBody(text_manager_cache_->GetEventResultText(EEventType::Patrol, 1));
	}
}

void UEventManager::Event_Patrol_FourthOptionResult()
{

	bool is_succeed = URandomNumberGeneratorSubsystem::Get(GetWorld())->RandBool();

	if (is_succeed)
	{
		global_buff_subsystem_->AddBuff(EGlobalBuffType::Patrol_RandomBuff4);
		event_widget_cache_->UpdateTextBody(text_manager_cache_->GetEventResultText(EEventType::Patrol, 0));
	}
	else
	{
		global_buff_subsystem_->AddBuff(EGlobalBuffType::Patrol_RandomDebuff4);
		event_widget_cache_->UpdateTextBody(text_manager_cache_->GetEventResultText(EEventType::Patrol, 1));
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
