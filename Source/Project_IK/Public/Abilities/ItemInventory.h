/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 10.19.2024
Summary : Header file for Item inventory.
					It contains a technical data of items.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Structs/TargetResult.h"
#include "ItemInventory.generated.h"

class UItem;
class UItemKeepOrDiscardWidget;
struct FItemData;

/**
 * 
 */

UCLASS(Blueprintable)
class PROJECT_IK_API UItemInventory : public UObject
{
	GENERATED_BODY()
	
public:
	static constexpr int32 INVENTORY_CAPACITY = 3;

	void AddItem(UItem* item, TFunction<void()> OnConfirm = []() {});
	void AddItem(FItemData item_data, TFunction<void()>OnConfirm = []() {});
	void AddItems(TArray<FItemData> item_data, TFunction<void()>OnConfirm = []() {});

	void UseItem(int32 item_idx, FTargetResult target_result);

	UItem* GetItem(int32 index) const;

	UFUNCTION(BlueprintCallable)
	void RemoveItem(int32 index);

	void ClearItems();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TSubclassOf<UItem> item_class_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	TSubclassOf<UItemKeepOrDiscardWidget> item_keep_discard_class_;
	
protected:
	void CallKeepDiscardUI(UItem* item_added, TFunction<void()>OnConfirm);
	void CallKeepDiscardUI(FItemData item_added, TFunction<void()>OnConfirm);
	void CallKeepDiscardUI(TArray<FItemData> item_added, TFunction<void()>OnConfirm);

	UFUNCTION()
	void OnKeepDiscardFinished(TArray<FItemData> item_data);
	
	void ClearItemKeepOrDiscardWidget();

	TFunction<void()> OnConfirm_;

	UPROPERTY()
	TArray<TObjectPtr<UItem>> item_inventory_;

	UPROPERTY()
	TObjectPtr<UItemKeepOrDiscardWidget> item_keep_discard_;
};
