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

#include "Components/Button.h"
#include "Managers/EnumCluster.h"
#include "Structs/EventData.h"
#include "UI/EventWidget.h"
#include "WorldSettings/IKGameInstance.h"

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
				return *event_table_->FindRow<FEventData>(FName("EventType_1"), TEXT(""));
			
			case 1:
				return *event_table_->FindRow<FEventData>(FName("EventType_2"), TEXT(""));
			
			case 2:
				return *event_table_->FindRow<FEventData>(FName("EventType_3"), TEXT(""));
			
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
	case EEventType::EventType_1:
		widget->button_1_->OnClicked.AddDynamic(this, &UEventManager::Event_1_FirstOptionResult);
		widget->button_2_->OnClicked.AddDynamic(this, &UEventManager::Event_1_SecondOptionResult);
		widget->button_3_->OnClicked.AddDynamic(this, &UEventManager::Event_1_ThirdOptionResult);
		break;

	case EEventType::EventType_2:
		widget->button_1_->OnClicked.AddDynamic(this, &UEventManager::Event_2_FirstOptionResult);
		widget->button_2_->OnClicked.AddDynamic(this, &UEventManager::Event_2_SecondOptionResult);
		widget->button_3_->OnClicked.AddDynamic(this, &UEventManager::Event_2_ThirdOptionResult);
		break;

	case EEventType::EventType_3:
		widget->button_1_->OnClicked.AddDynamic(this, &UEventManager::Event_3_FirstOptionResult);
		widget->button_2_->OnClicked.AddDynamic(this, &UEventManager::Event_3_SecondOptionResult);
		widget->button_3_->OnClicked.AddDynamic(this, &UEventManager::Event_3_ThirdOptionResult);
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

//Event 1: 재화
void UEventManager::Event_1_FirstOptionResult()
{
	inventory_manager_->AddCredits(10);
}

void UEventManager::Event_1_SecondOptionResult()
{
	inventory_manager_->AddCredits(-10);
}

void UEventManager::Event_1_ThirdOptionResult()
{
	inventory_manager_->AddCredits(inventory_manager_->GetCredits());
}

//Event 2: 장비
void UEventManager::Event_2_FirstOptionResult()
{
	//inventory_manager_->AddEquipment(EWeaponType::AssaultRifle_B);
}

void UEventManager::Event_2_SecondOptionResult()
{
	//inventory_manager_->AddEquipment(EActiveSkillType::Thunder);
}

void UEventManager::Event_2_ThirdOptionResult()
{
	//inventory_manager_->AddEquipment(EActiveSkillType::Thunder);
}

//Event 3: 룬
void UEventManager::Event_3_FirstOptionResult()
{
	//inventory_manager_->AddRune(ERuneSetType::Chariot, 0);
}

void UEventManager::Event_3_SecondOptionResult()
{
	//inventory_manager_->AddRune(ERuneSetType::Chariot, 1);
}

void UEventManager::Event_3_ThirdOptionResult()
{
	//inventory_manager_->AddRune(ERuneSetType::Chariot, 2);
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
