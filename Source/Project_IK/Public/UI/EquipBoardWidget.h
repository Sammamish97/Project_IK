/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 3.10.2025
Summary : Header file for Equip Board widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EquipBoardWidget.generated.h"

class UInventorySlot;
UCLASS()
class PROJECT_IK_API UEquipBoardWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativePreConstruct() override;
	void LoadEquipInventory(int32 hero_idx);
	
private:
	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<UInventorySlot> weapon_;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<UInventorySlot> passive_skill_;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<UInventorySlot> active_skill_;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta=(AllowPrivateAccess=true, BindWidget))
	TObjectPtr<UInventorySlot> oopart_;
	
	UPROPERTY(Transient)
	TArray<TObjectPtr<UInventorySlot>> owner_equip_array_;
};
