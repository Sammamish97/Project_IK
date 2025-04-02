/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 03.03.2025
Summary : Header file of UI that contains a button to go to Main menu.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/ToMainMenuWidget.h"

#include "Kismet/GameplayStatics.h"

#include "Components/Button.h"

FReply UToMainMenuWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	// Consider any key input to be button pressed.
	OnWidgetOpenButtonClicked();

	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

void UToMainMenuWidget::NativeConstruct()
{
	main_menu_button_->OnClicked.AddDynamic(this, &UToMainMenuWidget::OnWidgetOpenButtonClicked);
}

void UToMainMenuWidget::NativeDestruct()
{

	if (main_menu_button_->OnClicked.IsBound())
	{
		main_menu_button_->OnClicked.Clear();
	}
}

void UToMainMenuWidget::OnWidgetOpenButtonClicked()
{
	UWorld* world = GetWorld();
	if (world)
	{
		UGameplayStatics::OpenLevel(world, FName("Mainmenu"));
	}
}