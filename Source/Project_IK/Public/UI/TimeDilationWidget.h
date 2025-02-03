/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 2.2.2025
Summary : Header file for UI to control TimeDilation works.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimeDilationWidget.generated.h"

class UButton;
class UTextBlock;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UTimeDilationWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	static constexpr float BASE_SPEED = 1.f;
	static constexpr float ACC_SPEED = 2.f;
	static constexpr float RAPID_SPEED = 3.f;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION()
	void OnButtonClicked();

	void ChangeDilation();

	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UButton> button_;
	UPROPERTY(VisibleAnywhere, meta = (BindWidget))
	TObjectPtr<UTextBlock> text_;

	float current_dilation_;
};
