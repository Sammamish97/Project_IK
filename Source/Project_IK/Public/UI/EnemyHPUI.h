/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.23.2025
Summary : Header file for Enemy HP UI.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#pragma once

#include "CoreMinimal.h"
#include "HPUICore.h"
#include "EnemyHPUI.generated.h"

class UHPUICore;
class UBuffContainer;
class UBuffPopupWidget;

UCLASS()
class PROJECT_IK_API UEnemyHPUI : public UUserWidget
{
	GENERATED_BODY()
public:
	void InitEnemyHPUI(UBuffPopupWidget* popup_widget);
	TObjectPtr<UHPUICore> GetHPUICore();
	TObjectPtr<UBuffContainer> GetBuffContainer();

	UFUNCTION()
	void OnToggleDetailMode(bool on_focus_mode);

private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHPUICore> hp_widget_;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBuffContainer> buff_container_;
};
