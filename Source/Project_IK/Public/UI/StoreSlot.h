/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 01.17.2024
Summary : Header file for a slot UserWidget for Store.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/RewardData.h"
#include "StoreSlot.generated.h"

class UStoreWidget;
class UCheckboxButtonWidget;
class UTextBlock;
class UBorder;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStoreSlotClickedDelegate);

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UStoreSlot : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;

public:
	void SetItemData(const FRewardData& item_data);
	
	UFUNCTION(BlueprintCallable)
	void SetStoreWidgetCache(UStoreWidget* store_widget);
	UFUNCTION(BlueprintCallable)
	void SetTexture(UTexture2D* texture);
	UFUNCTION(BlueprintCallable)
	void SetPrice(int32 price);
	UFUNCTION(BlueprintCallable)
	int32 GetPrice() const;

	UFUNCTION(BlueprintCallable)
	bool IsChecked() const;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnStoreSlotClickedDelegate OnStoreSlotClickedDelegate;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION()
	void ForwardButtonClick();

	int32 price_;
	FRewardData item_data_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCheckboxButtonWidget> checkbox_button_;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> price_text_;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UBorder> rune_idx_border_;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> rune_idx_text_;
	
	UPROPERTY()
	TObjectPtr<UStoreWidget> store_widget_cache_;

	UPROPERTY()
	TObjectPtr<UTextManager> text_manager_cache_;
};
