/******************************************************************************
Copyright(C) 2025
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 04.08.2025
Summary : Header file for equipment reward widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/CheckboxButtonWidget.h"
#include "EquipmentRewardWidget.generated.h"

class UUniformGridPanel;
class UHorizontalBox;
class URewardSelectWidget;
class UTextBlock;
class UGridPanel;
class UCheckboxButtonWidget;
class UButton;

UCLASS()
class PROJECT_IK_API UEquipmentRewardWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void IncreaseSelectedCounter();
	void DecreaseSelectedCounter();
	bool AbleToSelectMoreReward();
	
	UFUNCTION()
	void OnConfirmButtonClicked();

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> text_max_selectables_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUniformGridPanel> reward_container_;

	UPROPERTY()
	TArray<TObjectPtr<URewardSelectWidget>> reward_widgets_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> confirm_button_;

public:
	static constexpr int32 NUM_CANDIDATES = 6;
	static constexpr int32 MAX_CHOICE = 3;

	int32 selected_amount = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<URewardSelectWidget> reward_widget_class_;
};