/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 03.03.2025
Summary : Header file of UI that contains a button to go to Main menu.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ToMainMenuWidget.generated.h"

class UButton;

/**
 * 
 */
UCLASS()
class PROJECT_IK_API UToMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:


protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION()
	void OnWidgetOpenButtonClicked();

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> main_menu_button_;

};
