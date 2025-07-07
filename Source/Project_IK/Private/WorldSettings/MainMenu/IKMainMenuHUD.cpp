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
#include "UI/ButtonToGoMapLevel.h"

void AIKMainMenuHUD::BeginPlay()
{
	if (map_level_opener_class_)
	{
		map_level_opener_ = CreateWidget<UButtonToGoMapLevel>(GetOwningPlayerController(), map_level_opener_class_);
		if (map_level_opener_)
		{
			map_level_opener_->AddToViewport();
		}
	}
}
