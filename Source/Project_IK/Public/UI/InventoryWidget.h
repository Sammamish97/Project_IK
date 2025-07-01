/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 2.06.2025
Summary : Header file for inventory widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class UButton;
class UEquipSlot;
class UInventoryManager;
class UHeroEquipBoardWidget;
class URuneBoardWidget;
class UWidgetSwitcher;

UCLASS(Blueprintable)
class PROJECT_IK_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	
	UFUNCTION(BlueprintCallable)
	void InitInventoryWidget(UInventoryManager* inventory_manager);

	UFUNCTION(BlueprintCallable)
	void UpdateInventoryData(int32 hero_idx);

	UFUNCTION(BlueprintCallable)
	void LoadInventoryData(int32 hero_idx);

private:

	int32 hero_idx_cache_ = 0.f;
	UPROPERTY(Transient)
	TObjectPtr<UInventoryManager> inventory_manager_cache_;
	
	UPROPERTY(Transient)
	TObjectPtr<class UDataTableManager> data_table_cache_;

	//
	
	// UPROPERTY(meta = (BindWidget))
	// TObjectPtr<UEquipSlot> support_skill_0_;
	//
	// UPROPERTY(meta = (BindWidget))
	// TObjectPtr<UEquipSlot> support_skill_1_;
	//
	// UPROPERTY(meta = (BindWidget))
	// TObjectPtr<UEquipSlot> support_skill_2_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHeroEquipBoardWidget> hero_board_0_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHeroEquipBoardWidget> hero_board_1_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHeroEquipBoardWidget> hero_board_2_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHeroEquipBoardWidget> hero_board_3_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<URuneBoardWidget> rune_board_;
};
