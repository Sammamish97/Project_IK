/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 12.28.2024
Summary : Source file of HUD for Gotcha level.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "WorldSettings/GotchaWorld/IKGotchaHUD.h"

#include "Blueprint/UserWidget.h"

void AIKGotchaHUD::BeginPlay()
{
	Super::BeginPlay();

	UWorld* world = GetWorld();

	if (widget_class_)
	{
		widget_ = CreateWidget<UUserWidget>(world, widget_class_);
		if (widget_)
		{
			widget_->AddToViewport();
		}
	}

}
