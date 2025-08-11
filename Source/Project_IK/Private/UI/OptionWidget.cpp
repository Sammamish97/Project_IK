/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.06.2025
Summary : Source file for option widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/OptionWidget.h"
#include "Components/Button.h"

void UOptionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	resume_button_->OnClicked.AddDynamic(this, &UOptionWidget::OnResumeButtonClicked);
	to_main_menu_button_->OnClicked.AddDynamic(this, &UOptionWidget::OnToMainMenuButtonClicked);
	quit_game_button_->OnClicked.AddDynamic(this, &UOptionWidget::OnQuitGameButtonClicked);
}

void UOptionWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UOptionWidget::OnResumeButtonClicked()
{
}

void UOptionWidget::OnToMainMenuButtonClicked()
{
}

void UOptionWidget::OnQuitGameButtonClicked()
{
}
