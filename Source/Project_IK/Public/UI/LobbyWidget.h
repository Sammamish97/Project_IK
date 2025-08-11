/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.06.2025
Summary : Header file for Lobby widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyWidget.generated.h"

class UPerkUnlockWidget;
class UButton;

UCLASS()
class PROJECT_IK_API ULobbyWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	UFUNCTION()
	void OnOpenPerkTreeButtonClicked();

	UFUNCTION()
	void OnBeginRunButtonClicked();
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> open_perk_tree_button_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> begin_run_button_;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UPerkUnlockWidget> perk_unlock_widget_;

	bool is_perk_unlock_widget_opened = false;
};
