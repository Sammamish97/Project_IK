/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.06.2025
Summary : Header file for inventory manager.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Structs/InventorySlotData.h"
#include "Structs/RuneData.h"
#include "UObject/Object.h"
#include "InventoryManager.generated.h"

UCLASS()
class PROJECT_IK_API UInventoryManager : public UObject
{
	GENERATED_BODY()

public:
	void InitInventoryManager();
	bool AddEquipment(EGearType type, EWeaponType weapon_type);
	bool AddEquipment(EGearType type, EPassiveSkillType passive_skill_type);
	bool AddEquipment(EGearType type, EActiveSkillType active_skill_type);
	bool AddEquipment(EGearType type, EOopartType oopart_type);

	bool AddRune(FRuneData rune_data);
	
	void RemoveEquipItem(int index);
	void RemoveRuneItem(int index);
	
	TArray<FInventorySlotData>& GetEquipStorageData();
	TArray<FRuneData>& GetRuneStorageData();

	void UpdateEquipStorage(const TArray<FInventorySlotData>& input);
	
	int32 GetMaxInventorySize();

	UFUNCTION(BlueprintCallable)
	void SetCredits(int32 currency);
	UFUNCTION(BlueprintCallable)
	int32 GetCredits() const;

	UFUNCTION(BlueprintCallable)
	void SetPerkPoints(int32 points);
	int32 GetPerkPoints() const;

private:
	int32 GetEquipmentEmptyIndex() const;
	int32 GetRuneEmptyIndex() const;

	void InitEquipInventory();
	void InitRuneInventory();
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TObjectPtr<class UDataTableManager> data_table_manager_cache_;
	
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TArray<FInventorySlotData> equipment_storage_;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TArray<FRuneData> rune_storage_;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	int32 max_inventory_size_;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	int32 credits_;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	int32 perk_points_;
};
