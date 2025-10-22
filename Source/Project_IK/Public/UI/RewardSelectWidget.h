/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.5.2025
Summary : Header file for Reward Select Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Structs/RewardData.h"
#include "RewardSelectWidget.generated.h"

class UBorder;
class UEquipmentRewardWidget;
class UTextBlock;
class UImage;
class UCheckBox;
class UBasicPopupWidget;
class UTextManager;

UCLASS()
class PROJECT_IK_API URewardSelectWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	
	void SetRewardData(const FActiveSkillData& data);
	void SetRewardData(const FPassiveSkillData& data);
	void SetRewardData(const FRuneData& data);
	void SetRewardData(const FWeaponData& data);

	void SetEquipmentWidgetCache(UEquipmentRewardWidget* equipment_widget_ptr);
	const FRewardData& GetRewardData();

	UFUNCTION()
	void OnCheckBoxClicked(bool checked);

	bool GetIsChecked();
	
private:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCheckBox> check_box_;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> thumbnail_;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UBorder> rune_idx_border_;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> rune_idx_text_;
	
	UPROPERTY(Transient)
	TObjectPtr<UEquipmentRewardWidget> equipment_reward_widget_cache_;

	UPROPERTY()
	TObjectPtr<UTextManager> text_manager_cache_;

	FRewardData reward_data_;
};
