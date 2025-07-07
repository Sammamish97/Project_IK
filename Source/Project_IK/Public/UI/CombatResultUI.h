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
enum class EHeroType : uint8;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UCombatResultUI : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual bool Initialize() override;

	void UpdateResults(const TMap<EHeroType, float>& damage_map);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UCombatResultBlock> combat_result_block_widget_class_;

protected:
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void InitializeRootWidget();
	void InitializeChildWidgets();

	void PopulateWidgets(const TMap<EHeroType, TObjectPtr<AActor>>& hero_containers);

	void UpdateHPBars(float InDeltaTime);

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	void UpdateInjuredNotifiers(float InDeltaTime);

protected:
	// Widget pointers
	UPROPERTY()
	TObjectPtr<UCanvasPanel> root_canvas_panel_;

	UPROPERTY()
	TObjectPtr<UBorder> UI_background_;

	UPROPERTY()
	TObjectPtr<UVerticalBox> widgets_holder_;

	UPROPERTY()
	TObjectPtr<UBorder> title_holder_;

	UPROPERTY()
	TObjectPtr<UTextBlock> title_;

	UPROPERTY()
	TObjectPtr<UHorizontalBox> blocks_holder_;

	UPROPERTY()
	TArray<TObjectPtr<UCombatResultBlock>> blocks_;

	// End of widget pointers

	TArray<float> hp_ratio_before_;
	TArray<float> hp_ratio_after_;

	float HP_timer_;

	float injury_timer_;
};
