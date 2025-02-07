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

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> scroll_panel_;

	UPROPERTY()
	TArray<TObjectPtr<UButton>> buttons_;

	UPROPERTY()
	// FIntPoint<StartIndex, EndIndex>
	TMap < FIntPoint, TObjectPtr<UProgressBar>> links_;
};
