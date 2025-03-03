/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 03.03.2025
Summary : Header file of UI that contains a button to go to Mainmenu.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/WidgetOpenerUI.h"

#include "Kismet/GameplayStatics.h"

#include "Components/Button.h"


void UWidgetOpenerUI::NativeConstruct()
{
	widget_opener_button_->OnClicked.AddDynamic(this, &UWidgetOpenerUI::OnWidgetOpenButtonClicked);
}

void UWidgetOpenerUI::NativeDestruct()
{
	if (widget_opener_button_->OnClicked.IsBound())
	{
		widget_opener_button_->OnClicked.Clear();
	}
}

void UWidgetOpenerUI::OnWidgetOpenButtonClicked()
{

	if (widget_class_)
	{

		widget_ = CreateWidget<UUserWidget>(UGameplayStatics::GetPlayerController(GetWorld(), 0), widget_class_);
		if (widget_)
		{
			widget_->AddToViewport();
		}
	}
}
