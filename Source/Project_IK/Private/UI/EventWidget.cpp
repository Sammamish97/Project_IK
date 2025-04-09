/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 04.04.2025
Summary : Source file for Event Level Widget class.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/EventWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Structs/EventData.h"

void UEventWidget::InitEventWidget(FEventData input_data)
{
	situation_->SetBrushFromTexture(input_data.situation_);
	event_title_->SetText(input_data.event_title_);
	text_body_->SetText(input_data.text_body_);
	first_option_->SetText(input_data.option_1);
	second_option_->SetText(input_data.option_2);
	third_option_->SetText(input_data.option_3);
}

void UEventWidget::ClearButtonBinding()
{
	if (button_1_->OnClicked.IsBound())
	{
		button_1_->OnClicked.Clear();
	}
	if (button_2_->OnClicked.IsBound())
	{
		button_2_->OnClicked.Clear();
	}
	if (button_3_->OnClicked.IsBound())
	{
		button_3_->OnClicked.Clear();
	}
}

void UEventWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UEventWidget::NativeDestruct()
{
	ClearButtonBinding();
	Super::NativeDestruct();
}
