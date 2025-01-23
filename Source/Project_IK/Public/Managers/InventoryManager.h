/******************************************************************************
Copyright(C) 2024
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 1.10.2025
Summary : Header file for the inventory Manager.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Managers/EnumCluster.h"
#include "Structs/DPData.h"
#include "InventoryManager.generated.h"
class UInventoryWidget;
UCLASS(Blueprintable)
class PROJECT_IK_API UInventoryManager : public UObject
{
	GENERATED_BODY()

private:
	int GetEmptyIndex() const;

public:
	void InitInventory();
	bool AddDP(EDPType type);
	void RemoveDP(int index);
	
	TArray<FDPData>& GetInventory();
	int GetInventorySize();

	UFUNCTION(BlueprintCallable)
	void SetCredits(int32 currency);
	UFUNCTION(BlueprintCallable)
	int32 GetCredits() const;

private:
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TArray<FDPData> inventory_;
	
	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	int inventory_size_;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	int credits_;
};
