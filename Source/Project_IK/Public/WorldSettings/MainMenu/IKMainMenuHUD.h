/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 03.02.2025
Summary : Header file for HUD in MainMenu.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "IKMainMenuHUD.generated.h"

class UMainMenuWidget;

UCLASS()
class PROJECT_IK_API AIKMainMenuHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	// Need to add TSubclassOf and ptr of MapWidget
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UMainMenuWidget> main_menu_widget_class_;
	
protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<UMainMenuWidget> main_menu_widget_;
};
