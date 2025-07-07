/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 06.26.2025
Summary : Header file of UI that contains a button to open a map level.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ButtonToGoMapLevel.generated.h"

/**
 * 
 */

class UButton;

UCLASS(Blueprintable)
class PROJECT_IK_API UButtonToGoMapLevel : public UUserWidget
{
	GENERATED_BODY()
public:
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION()
	void OnMapOpenerButtonClicked();

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> map_opener_button_;
};
