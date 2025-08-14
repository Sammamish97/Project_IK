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
#include "Managers/EnumCluster.h"
#include "PerkUnlockWidget.generated.h"

class UCanvasPanel;
class UVerticalBox;
class UHorizontalBox;
class UButton;
class UProgressBar;
class UImage;
class UTextBlock;

enum class EHeroType : uint8;
struct FPerkNode;

class UConfirmationWidget;

UCLASS()
class PROJECT_IK_API UPerkUnlockWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UConfirmationWidget> confirmation_widget_class_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node")
	FButtonStyle lockable_node_style_;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node")
	FSlateBrush unlocked_disabled_brush_;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node")
	FSlateBrush locked_disabled_brush_;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Node")
	FMargin node_margin_;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Link")
	FLinearColor link_fill_color_;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Link")
	FProgressBarStyle lockable_progress_bar_style_;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Link")
	FProgressBarStyle locked_progress_bar_style_;

	static constexpr float link_animation_interval_ = 0.01f;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void ConstructPerkTree();
	void ConstructLinks();

	UVerticalBox* ConstructNewTreeBox();
	UHorizontalBox* ConstructNewTreeLevel(UVerticalBox* tree_box);
	UButton* ConstructNewTreeNode(UHorizontalBox* level_box);
	void CustomizeButtonByNode(UButton* button, const FPerkNode& node);

	UProgressBar* ConstructLink(int32 start_index, int32 start_max_index, int32 end_index, int32 end_max_index, int32 level);
	FVector2D CalculateNodePosition(int32 index, int32 size, int32 level);

	UFUNCTION()
	void OnButtonClicked();
	UFUNCTION()
	void OnConfirmed();

	void ClearButtonDelegates();
	void StartLinkAnimation(TArray<TWeakObjectPtr<UProgressBar>> links);
	void UpdateLinkAnimation();

	void InitWidgets();

	// A function invoked when users actually clicked the button.
	bool UnlockPerk(int32 clicked_index);
	// A function to make the button looks clicked.
	void MakeButtonUnlockedVisually(int32 clicked_index, bool is_animate_links = false);

	void ClearWidgets();

	int32 GetAccumulatedPerkCost(int32 perk_index);

	// A function starts recursive function.
	void UpdateCosts(const TSet<int32>& progress);
	// A helper recursive function.
	void AccumulateCost(const TArray<FPerkNode>& tree, const TSet<int32>& progress, int32 current_node_index, int32 accumulated_cost);
	void LockUnpayableButtons();		

	bool OnButtonClickedDFS(const TArray<FPerkNode>& tree, int32 current_node_index, TArray<int32>& path);

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> scroll_panel_;

	UPROPERTY()
	TArray<TObjectPtr<UButton>> buttons_;

	UPROPERTY()
	TArray<int32> costs_;

	UPROPERTY()
	// FIntPoint<StartIndex, EndIndex>
	TMap < FIntPoint, TObjectPtr<UProgressBar>> links_;


	FTimerHandle link_animation_timer_handle_;
	UPROPERTY(Transient)
	TArray<TWeakObjectPtr<UProgressBar>> links_animating_;
	UPROPERTY(Transient)
	float link_animation_percent_;


	TArray<int32> path_to_selected_node_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> perk_points_text_;

	UPROPERTY()
	TObjectPtr<UConfirmationWidget> confirmation_widget_;
};
