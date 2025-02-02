/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 2.2.2025
Summary : Source file for UI to control TimeDilation works.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/TimeDilationWidget.h"

#include "Kismet/GameplayStatics.h"
#include "WorldSettings/IKGameModeBase.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

void UTimeDilationWidget::NativeConstruct()
{
	button_->OnClicked.AddDynamic(this, &UTimeDilationWidget::OnButtonClicked);

	current_dilation_ = BASE_SPEED;
}

void UTimeDilationWidget::NativeDestruct()
{
	if (button_->OnClicked.IsBound())
	{
		button_->OnClicked.Clear();
	}
}

void UTimeDilationWidget::OnButtonClicked()
{
	TWeakObjectPtr<AIKGameModeBase> game_mode = Cast<AIKGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	if (game_mode.IsValid())
	{
		ChangeDilation();

		game_mode->SetGlobalTimeDilation(current_dilation_);

		text_->SetText(FText::Format(FText::FromString("x{0}"), FText::AsNumber(current_dilation_)));
	}
}

void UTimeDilationWidget::ChangeDilation()
{
	if (current_dilation_ <= BASE_SPEED)
	{
		current_dilation_ = ACC_SPEED;
	}
	else if (current_dilation_ <= ACC_SPEED)
	{
		current_dilation_ = RAPID_SPEED;
	}
	else
	{
		current_dilation_ = BASE_SPEED;
	}
}
