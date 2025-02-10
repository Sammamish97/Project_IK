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
#include "UObject/Object.h"
#include "HeroInventoryManager.generated.h"

UCLASS()
class PROJECT_IK_API UHeroInventoryManager : public UObject
{
	GENERATED_BODY()
private:
	int32 GetEmptyIndex() const;
	
public:
	void InitInventory();
	bool AddItem(EGearType type, EArmorType armor_type);
	bool AddItem(EGearType type, ETrinketType trinket_type);
	bool AddItem(EGearType type, EWeaponType weapon_type);
	bool AddItem(EGearType type, EPassiveSkillType passive_skill_type);

	
	void RemoveItem(int index);
	
	TArray<FInventorySlotData>& GetInventory();
	int32 GetInventorySize();

	UFUNCTION(BlueprintCallable)
	void SetCredits(int32 currency);
	UFUNCTION(BlueprintCallable)
	int32 GetCredits() const;
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TArray<FInventorySlotData> inventory_;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	int32 inventory_size_;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	int32 credits_;
};
