/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.06.2025
Summary : Header file for main menu widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UButton;
class USettingWidget;

UCLASS()
class PROJECT_IK_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION()
	void OnNewGameButtonClicked();

	UFUNCTION()
	void OnContinueButtonClicked();

	UFUNCTION()
	void OnSettingButtonClicked();

	UFUNCTION()
	void OnExitButtonClicked();

protected:
	bool IsContinuable();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<USettingWidget> setting_ui_class_;
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> new_game_button_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> continue_button_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> setting_button_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> exit_button_;
};
