/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 11.25.2024
Summary : Header file for UI to pick an item.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ItemPickerUI.generated.h"

class UCanvasPanel;
class UBorder;
class UVerticalBox;
class UTextBlock;
class UHorizontalBox;
class UButton;
class UImage;
class UCheckBox;
struct FItemData;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UItemPickerUI : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;


protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void InitializeRootWidget();
	void InitializeChildWidgets();

	void FadeInOutHighlight(float InDeltaTime);

	UFUNCTION()
	void SelectButtonBindingFunc();
	UFUNCTION()
	void ItemButtonOnClicked();
	UFUNCTION()
	FVector2D GetButtonPosition(int32 ButtonIndex) const;

	UFUNCTION()
	void OnSkipCheckedStateChanged(bool bIsChecked);

	UFUNCTION()
	void GoToNextStep() const;

	UPROPERTY()
	TObjectPtr<UCanvasPanel> root_canvas_panel_;
	UPROPERTY()
	TObjectPtr<UBorder> background_;
	UPROPERTY()
	TObjectPtr<UVerticalBox> widgets_holder_;
	UPROPERTY()
	TObjectPtr<UTextBlock> title_;
	UPROPERTY()
	TObjectPtr<UTextBlock> description_;
	UPROPERTY()
	TObjectPtr<UHorizontalBox> buttons_holder_;
	UPROPERTY()
	TArray<TObjectPtr<UButton>> buttons_;
	UPROPERTY()
	TObjectPtr<UVerticalBox> skip_holder_;
	UPROPERTY()
	TObjectPtr<UCheckBox> skip_checkbox_;
	UPROPERTY()
	TObjectPtr<UTextBlock> skip_text_;
	UPROPERTY()
	TObjectPtr<UButton> select_button_;
	UPROPERTY()
	TObjectPtr<UImage> highlight_image_;

	TArray<FItemData*> item_candidates_;

	int32 selected_button_index_;

	float highlight_current_opacity_;
	float highlight_fade_speed_;
	bool is_highligh_fade_in_;
};
