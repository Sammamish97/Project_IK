/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.06.2025
Summary : Source file for Pause manager.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "Managers/PauseManager.h"
#include "UI/PauseWidget.h"
#include "Blueprint/UserWidget.h"

void UPauseManager::TogglePause(bool on_pause)
{
	if (on_pause)
	{
		OpenPauseWidget();
	}
	else
	{
		ClosePauseWidget();
	}
}

void UPauseManager::OpenPauseWidget()
{
	if (pause_widget_class_)
	{
		if (pause_widget_ == nullptr)
		{
			pause_widget_ = CreateWidget<UPauseWidget>(GetWorld(), pause_widget_class_);
		}
		pause_widget_->AddToViewport();
	}
}

void UPauseManager::ClosePauseWidget()
{
	if (pause_widget_)
	{
		pause_widget_->RemoveFromParent();
	}
}
