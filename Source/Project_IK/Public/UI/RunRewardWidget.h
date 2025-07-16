/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 03.31.2025
Summary : Source file for Run reward widget.
					It distributes reward for completing a run.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RunRewardWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API URunRewardWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
protected:

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> perk_points_text_;
	
	int32 perk_points_reward_ = 10;
};
