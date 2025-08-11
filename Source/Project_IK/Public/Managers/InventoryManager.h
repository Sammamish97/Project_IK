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
#include "UObject/Object.h"
#include "InventoryManager.generated.h"

class UDataTableManager;
struct FWrapperEquipmentData;
UCLASS(Blueprintable, Abstract)
class PROJECT_IK_API UInventoryManager : public UObject
{
	GENERATED_BODY()

public:
	void OpenInventoryWidgetReward(const FWrapperEquipmentData& rewards);
	
	UFUNCTION(BlueprintCallable)
	void SetCredits(int32 currency);
	UFUNCTION(BlueprintPure)
	int32 GetCredits() const;
	UFUNCTION(BlueprintCallable)
	void AddCredits(int32 currency);

	UFUNCTION(BlueprintCallable)
	void SetPerkPoints(int32 points);
	UFUNCTION(BlueprintPure)
	int32 GetPerkPoints() const;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Inventory", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UInventoryWidget> inventory_widget_class_;
	
	UPROPERTY()
	TObjectPtr<UInventoryWidget> inventory_widget_;
	
	UPROPERTY()
	TObjectPtr<UDataTableManager> data_table_manager_cache_;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	int32 credits_;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	int32 perk_points_;
};
