/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 1.21.2025
Summary : Header file for UI to check confirmation.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ConfirmationWidget.generated.h"

class UTextBlock;
class UButton;
class UBorder;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConfirmation);

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UConfirmationWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetText(FText text);


	FOnConfirmation OnConfirmation;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	UFUNCTION()
	void OnButtonClicked();

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> border_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> text_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> button_;
};
