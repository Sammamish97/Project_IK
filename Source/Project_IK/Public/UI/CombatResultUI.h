/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 11.17.2024
Summary : Header file for Combat Result UI class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CombatResultUI.generated.h"

class UCanvasPanel;
class UBorder;
class UVerticalBox;
class UTextBlock;
class UHorizontalBox;
class UCombatResultBlock;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UCombatResultUI : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;

	void UpdateResults(const TArray<AActor*>& heroes, const TMap<TWeakObjectPtr<AActor>, float>& damage_map);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UCombatResultBlock> combat_result_block_widget_class_;

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	virtual void NativeConstruct() override;

	void InitializeRootWidget();
	void InitializeChildWidgets();

	void SetHeroNumbers(int32 num);

	void UpdateHPBars(float InDeltaTime);

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	// Widget pointers
	UPROPERTY()
	TWeakObjectPtr<UCanvasPanel> root_canvas_panel_;

	UPROPERTY()
	TWeakObjectPtr<UBorder> UI_background_;

	UPROPERTY()
	TWeakObjectPtr<UVerticalBox> widgets_holder_;

	UPROPERTY()
	TWeakObjectPtr<UBorder> title_holder_;

	UPROPERTY()
	TWeakObjectPtr<UTextBlock> title_;

	UPROPERTY()
	TWeakObjectPtr<UHorizontalBox> blocks_holder_;

	UPROPERTY()
	TArray<TWeakObjectPtr<UCombatResultBlock>> blocks_;

	// End of widget pointers

	TArray<float> hp_ratio_before_;
	TArray<float> hp_ratio_after_;

	float HP_timer_;
};
