/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.06.2025
Summary : Header file for option widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OptionWidget.generated.h"

class UButton;
UCLASS()
class PROJECT_IK_API UOptionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION()
	void OnResumeButtonClicked();

	UFUNCTION()
	void OnToMainMenuButtonClicked();

	UFUNCTION()
	void OnQuitGameButtonClicked();
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> resume_button_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> to_main_menu_button_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> quit_game_button_;
};
