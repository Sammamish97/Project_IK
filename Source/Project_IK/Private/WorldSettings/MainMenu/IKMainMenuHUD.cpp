/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 03.02.2025
Summary : Header file for HUD in MainMenu.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "WorldSettings/MainMenu/IKMainMenuHUD.h"

// Need to call CreateWidget function
#include "Blueprint/UserWidget.h"
#include "UI/MainMenuWidget.h"

void AIKMainMenuHUD::BeginPlay()
{
	if (main_menu_widget_class_)
	{
		main_menu_widget_ = CreateWidget<UMainMenuWidget>(GetOwningPlayerController(), main_menu_widget_class_);
		if (main_menu_widget_)
		{
			main_menu_widget_->AddToViewport();
		}
	}
}