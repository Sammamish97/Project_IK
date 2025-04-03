/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 01.08.2025
Summary : Header file of widget that choose whether keep the item or discard.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemKeepOrDiscardWidget.generated.h"

class UGridPanel;
class UHorizontalBox;
class UButton;
class UCheckboxButtonWidget;
class UTextBlock;
struct FItemData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConfirmed, TArray<FItemData>, data);

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UItemKeepOrDiscardWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;

	void UpdateItems(TArray<FItemData> inventory_items, TArray<FItemData> candidates_items);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UCheckboxButtonWidget> check_box_button_class_;

	static constexpr int32 MAX_ROW = 5;

	UPROPERTY(BlueprintAssignable, Category = "Bindings")
	FOnConfirmed OnConfirmed;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	UFUNCTION()
	void OnConfirmButtonClicked();
	UFUNCTION()
	void OnCheckboxButtonClicked();
	bool ToggleCheckboxButton(UCheckboxButtonWidget* widget);

	void AddItemCheckboxInventory(FItemData item_data);
	void AddItemCheckboxCandidates(TArray<FItemData> item_data);

	// A grid panel to contains horizontal boxes that will contain image checkboxes.
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UGridPanel> horizontal_box_container_;
	// It is an array that contains the horizontal boxes.
	UPROPERTY()
	TArray<TObjectPtr<UHorizontalBox>> candidates_item_containers_;
	UPROPERTY()
	TArray<TObjectPtr<UCheckboxButtonWidget>> candidates_items_widgets_;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> item_text_;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UHorizontalBox> inventory_item_container_;
	UPROPERTY()
	TArray<TObjectPtr<UCheckboxButtonWidget>> inventory_items_widgets_;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> confirm_button_;

	TArray<FItemData> candidates_items_;
	TArray<FItemData> inventory_items_;

	UPROPERTY(Transient)
	int32 checked_items_num_;
};
