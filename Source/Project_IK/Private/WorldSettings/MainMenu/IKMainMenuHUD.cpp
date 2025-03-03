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
#include "UI/WidgetOpenerUI.h"

void AIKMainMenuHUD::BeginPlay()
{
	if (map_widget_opener_class_)
	{
		map_widget_opener_ = CreateWidget<UWidgetOpenerUI>(GetOwningPlayerController(), map_widget_opener_class_);
		if (map_widget_opener_)
		{
			map_widget_opener_->AddToViewport();
		}
	}
}
