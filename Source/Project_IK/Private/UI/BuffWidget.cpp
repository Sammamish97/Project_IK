/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.16.2025
Summary : Source file for Buff Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/BuffWidget.h"

#include "Components/ProgressBar.h"
#include "DataAssets/DisplayDataAsset.h"
#include "UI/BuffPopupWidget.h"

void UBuffWidget::InitWidget(UBuffPopupWidget* popup, UBuffContainer* container)
{
	buff_popup_ref_ = popup;
	container_ref_ = container;
}

void UBuffWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	buff_popup_ref_->SetBuffDetail(display_data_cache_);
}

void UBuffWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	buff_popup_ref_->ResetWidget();
}

void UBuffWidget::BeginBuffUI()
{
	SetVisibility(ESlateVisibility::Visible);
	is_available_ = false;

	if(display_data_cache_->thumbnail != nullptr)
	{
		FSlateBrush brush;
		brush.SetResourceObject(display_data_cache_->thumbnail);

		FProgressBarStyle style;
		style.BackgroundImage = brush;
    
		style.FillImage = brush;
		style.FillImage.TintColor = FLinearColor(0.2f, 0.2f, 0.2f);
    
		buff_image_->SetWidgetStyle(style);
	}
}

void UBuffWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (is_permanent_ == false && left_time_ > 0)
	{
		left_time_ -= InDeltaTime;
		left_time_ = FMath::Max(left_time_, 0.f);
		buff_image_->SetPercent(left_time_ / duration_);
	}
}

EBuffType UBuffWidget::GetCurBuffType() const
{
	return cur_buff_type_;
}

float UBuffWidget::GetDuration() const
{
	return duration_;
}

TObjectPtr<UDisplayDataAsset> UBuffWidget::GetDisplayDataCache() const
{
	return display_data_cache_;
}

bool UBuffWidget::GetIsPermanent() const
{
	return is_permanent_;
}

float UBuffWidget::GetLeftTime() const
{
	return left_time_;
}

FProgressBarStyle UBuffWidget::GetProgressBarStyle() const
{
	return buff_image_->GetWidgetStyle();
}

void UBuffWidget::ResetWidget()
{
	SetVisibility(ESlateVisibility::Hidden);
	left_time_ = 0.f;
	duration_ = 0.f;
	is_permanent_ = false;
	is_available_ = true;
	display_data_cache_ = nullptr;
	cur_buff_type_ = EBuffType::INVALID;
}

void UBuffWidget::SetWidget(const FProgressBarStyle& style, EBuffType buff_type, UDisplayDataAsset* data_cache,
	bool is_permanent, float duration, float left_time, bool is_available)
{
	if(is_available)
	{
		ResetWidget();
	}
	else
	{
		is_permanent_ = is_permanent;
		left_time_ = left_time;
		duration_ = duration;
		is_available_ = is_available;
		display_data_cache_ = data_cache;
		cur_buff_type_ = buff_type;
		buff_image_->SetWidgetStyle(style);
	}
}

bool UBuffWidget::IsWidgetAvailable() const
{
	return is_available_;
}
