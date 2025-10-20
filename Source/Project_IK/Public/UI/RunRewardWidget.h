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
enum class ERunResultType : uint8;

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
	
	void SetOnConfirm(TFunction<void()> on_confirm);

protected:
	// A function grants only once
	void GrantsPerkPoints();

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ERunResultType result_text_type_;

	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> event_num_text_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> store_num_text_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> combat_num_text_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> perk_points_text_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> text_body_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> click_to_return_text_;
	
	int32 perk_points_reward_ = 1;
	int32 combat_num_ = 0;
	int32 event_num_ = 0;
	int32 store_num_ = 0;

	TFunction<void()> on_confirm_;

	bool has_granted_ = false;
};
