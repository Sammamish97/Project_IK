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
/**
 * 
 */
UCLASS()
class PROJECT_IK_API UPerkUnlockWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	FButtonStyle default_node_style;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	void ConstructPerkTree();
	void ConstructLinks();

	UVerticalBox* ConstructNewTreeBox();
	UHorizontalBox* ConstructNewTreeLevel(UVerticalBox* tree_box);
	UButton* ConstructNewTreeNode(UHorizontalBox* level_box);

	void ConstructLink(UButton* start, UButton* end);

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCanvasPanel> scroll_panel_;

	UPROPERTY()
	TArray<TObjectPtr<UButton>> buttons_;

	FTimerHandle TimerHandle;
};
