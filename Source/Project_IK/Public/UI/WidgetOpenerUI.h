/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 03.03.2025
Summary : Header file of UI that contains a button to open a widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetOpenerUI.generated.h"

class UButton;

/**
 *
 */
UCLASS()
class PROJECT_IK_API UWidgetOpenerUI : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> widget_class_;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION()
	void OnWidgetOpenButtonClicked();

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> widget_opener_button_;

	UPROPERTY()
	TObjectPtr<UUserWidget> widget_;

};
