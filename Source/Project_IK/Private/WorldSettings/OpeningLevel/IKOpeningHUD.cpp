/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 9.29.2025
Summary : Source file for opening level HUD.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "WorldSettings/OpeningLevel/IKOpeningHUD.h"
#include "UI/OpeningWidget.h"
#include "Blueprint/UserWidget.h"

void AIKOpeningHUD::BeginPlay()
{
	Super::BeginPlay();
	
	if (opening_widget_class_)
	{
		opening_widget_ = CreateWidget<UOpeningWidget>(GetWorld(), opening_widget_class_);
		if (opening_widget_class_)
		{
			opening_widget_->AddToViewport();
		}
	}

	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		PC->bShowMouseCursor = true;
		PC->bEnableClickEvents = true;
		PC->bEnableMouseOverEvents = true;

		FInputModeGameAndUI Mode;
		Mode.SetWidgetToFocus(opening_widget_->TakeWidget());
		Mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		Mode.SetHideCursorDuringCapture(false);
		PC->SetInputMode(Mode);
	}
}
