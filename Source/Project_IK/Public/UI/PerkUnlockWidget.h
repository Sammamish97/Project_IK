/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 2.4.2025
Summary : Header file for UI to unlock heros' perks.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PerkUnlockWidget.generated.h"

class UCanvasPanel;
class UVerticalBox;
class UHorizontalBox;
class UButton;
class UProgressBar;
class UImage;
class UTextBlock;

enum class EHeroType : uint8;

/**
 *
 */
UCLASS()
class PROJECT_IK_API UPerkUnlockWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FButtonStyle default_node_style_;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FMargin node_margin_;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FLinearColor link_fill_color_;

	static constexpr float link_animation_interval_ = 0.01f;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void ConstructPerkTree();
	void ConstructLinks();

	UVerticalBox* ConstructNewTreeBox();
	UHorizontalBox* ConstructNewTreeLevel(UVerticalBox* tree_box);
	UButton* ConstructNewTreeNode(UHorizontalBox* level_box);

	UProgressBar* ConstructLink(int32 start_index, int32 start_max_index, int32 end_index, int32 end_max_index, int32 level);
	FVector2D CalculateNodePosition(int32 index, int32 size, int32 level);

	UFUNCTION()
	void OnButtonClicked();

	void ClearButtonDelegates();
	void StartLinkAnimation(TArray<TWeakObjectPtr<UProgressBar>> links);
	void UpdateLinkAnimation();

	UFUNCTION()
	void OnLeftButtonClicked();
	UFUNCTION()
	void OnRightButtonClicked();

	void UpdateHeroData();

	bool ButtonClicked(int32 clicked_index);
	void ClearWidgets();

	int32 GetPerkCost(int32 perk_index);

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> scroll_panel_;

	UPROPERTY()
	TArray<TObjectPtr<UButton>> buttons_;

	UPROPERTY()
	// FIntPoint<StartIndex, EndIndex>
	TMap < FIntPoint, TObjectPtr<UProgressBar>> links_;


	FTimerHandle link_animation_timer_handle_;
	UPROPERTY(Transient)
	TArray<TWeakObjectPtr<UProgressBar>> links_animating_;
	UPROPERTY(Transient)
	float link_animation_percent_;


	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> left_button_;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> portrait_image_;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> right_button_;

	EHeroType current_hero_type_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> perk_points_text_;
};
