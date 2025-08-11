/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.06.2025
Summary : Source file for Lobby level hud.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "WorldSettings/LobbyLevel/IKLobbyLevelHUD.h"
#include "Blueprint/UserWidget.h"
#include "UI/LobbyWidget.h"
void AIKLobbyLevelHUD::BeginPlay()
{
	if (lobby_widget_class_)
	{
		lobby_widget_ = CreateWidget<ULobbyWidget>(GetOwningPlayerController(), lobby_widget_class_);
		if (lobby_widget_)
		{
			lobby_widget_->AddToViewport();
		}
	}
}
