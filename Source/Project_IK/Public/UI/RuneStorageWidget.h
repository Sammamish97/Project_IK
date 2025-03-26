/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 3.11.2025
Summary : Header file for Rune Storage widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RuneStorageWidget.generated.h"

UCLASS()
class PROJECT_IK_API URuneStorageWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetCurSlotNum(int32 input_num);
	void UpdateRuneStorage();
	void LoadRuneStorage(int32 slot_num);
	void InitStorageData(TObjectPtr<class URuneBoardWidget> rune_boarda_ptr);
	int32 GetCurSlotNum();

private:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<class UWrapBox> wrap_box_;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta=(AllowPrivateAccess=true))
	TSubclassOf<class URuneSlotWidget> slot_BP_class_;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true))
	TArray<TObjectPtr<class URuneSlotWidget>> rune_storage_slots_;
	
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true))
	TObjectPtr<class UInventoryManager> inventory_manager_cache_;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true))
	TObjectPtr<class URuneBoardWidget> rune_board_cache_;

	UPROPERTY(Transient)
	int32 cur_slot_num_ = -1;
};