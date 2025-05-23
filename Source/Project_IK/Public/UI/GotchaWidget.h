/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 1.3.2025
Summary : Header file of user widget class to gotcha.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GotchaWidget.generated.h"

class UButton;
class UTextBlock;
class UGotchaResultWidget;

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECT_IK_API UGotchaWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UGotchaResultWidget> result_widget_class_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Textures")
	UTexture2D* credits_texture_;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	UFUNCTION()
	void BackSpace();
	UFUNCTION()
	void PullOne();
	UFUNCTION()
	void PullTen();

	void SetTickets(int32 tickets);

	void UpdateGotchaTicketCount();

	void Gotcha(int32 pulls);

	void ClearContainers();

	UFUNCTION()
	void StorePulledData();

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> back_space_;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> pull_one_button_;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> pull_ten_button_;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> tickets_count_text_;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UGotchaResultWidget> result_widget_;

	int32 pulled_credits_;

	int32 tickets_;
};
