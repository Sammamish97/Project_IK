/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 04.04.2025
Summary : Header file for Event Manager

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once
#include "CoreMinimal.h"
#include "Structs/EventData.h"
#include "UObject/Object.h"
#include "EventManager.generated.h"

class UEventDataAsset;
class UIKMaps;
enum class EHeroType : uint8;
struct FWrapperEquipmentData;

UCLASS(Blueprintable)
class PROJECT_IK_API UEventManager : public UObject
{
	GENERATED_BODY()

public:
	void InitEventManager(TObjectPtr<class UIKGameInstance> instance, TObjectPtr<class UInventoryManager> inventory_manager);
	FEventData GetRandomEventData();
	void BindEventResult(FEventData data, TObjectPtr<class UEventWidget> widget);
	void CountUpIsNegativeEventsRemoved();
	void CountDownIsNegativeEventsRemoved();
//
	UFUNCTION()
	void Event_AirStrike_FirstOptionResult();
	
	UFUNCTION()
	void Event_AirStrike_SecondOptionResult();

	UFUNCTION()
	void Event_AirStrike_ThirdOptionResult();
//
	UFUNCTION()
	void Event_Ambush_FirstOptionResult();
	
	UFUNCTION()
	void Event_Ambush_SecondOptionResult();

	UFUNCTION()
	void Event_Ambush_ThirdOptionResult();
//
	UFUNCTION()
	void Event_Trap_FirstOptionResult();
	
	UFUNCTION()
	void Event_Trap_SecondOptionResult();

	UFUNCTION()
	void Event_Trap_ThirdOptionResult();
	//
	UFUNCTION()
	void Event_EMP_FirstOptionResult();

	UFUNCTION()
	void Event_EMP_SecondOptionResult();

	UFUNCTION()
	void Event_EMP_ThirdOptionResult();
	//
	UFUNCTION()
	void Event_ProtocolSurvive_FirstOptionResult();

	UFUNCTION()
	void Event_ProtocolSurvive_SecondOptionResult();

	UFUNCTION()
	void Event_ProtocolSurvive_ThirdOptionResult();
	//
	UFUNCTION()
	void Event_ProtocolAssault_FirstOptionResult();

	UFUNCTION()
	void Event_ProtocolAssault_SecondOptionResult();

	UFUNCTION()
	void Event_ProtocolAssault_ThirdOptionResult();
	//
	UFUNCTION()
	void Event_ProtocolEfficiency_FirstOptionResult();

	UFUNCTION()
	void Event_ProtocolEfficiency_SecondOptionResult();

	UFUNCTION()
	void Event_ProtocolEfficiency_ThirdOptionResult();
	//
	UFUNCTION()
	void Event_AbandonedSupply_FirstOptionResult();

	UFUNCTION()
	void Event_AbandonedSupply_SecondOptionResult();

	UFUNCTION()
	void Event_AbandonedSupply_ThirdOptionResult();
	//
	UFUNCTION()
	void Event_Recon_FirstOptionResult();

	UFUNCTION()
	void Event_Recon_SecondOptionResult();

	UFUNCTION()
	void Event_Recon_ThirdOptionResult();
	//
	UFUNCTION()
	void Event_SetTrap_FirstOptionResult();
	//
	UFUNCTION()
	void Event_Core_FirstOptionResult();
	//
	UFUNCTION()
	void Event_Patrol_FirstOptionResult();

	UFUNCTION()
	void Event_Patrol_SecondOptionResult();

	UFUNCTION()
	void Event_Patrol_ThirdOptionResult();

	UFUNCTION()
	void Event_Patrol_FourthOptionResult();

private:
	void SetNextNodeToElite(UIKMaps* map, int32 row, int32 col, int32 left_level);
	bool IsNegativeEventsRemoved() const;
	void OpenInventory(FWrapperEquipmentData data);

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UEventDataAsset> event_data_asset_;

	TWeakObjectPtr<class UGlobalBuffSubsystem> global_buff_subsystem_;
	TWeakObjectPtr<class UInventoryManager> inventory_manager_;

	int32 only_positive_event_counter_ = 0;
};
