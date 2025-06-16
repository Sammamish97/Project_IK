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

void UBuffWidget::InitWidget(int32 index, UBuffContainer* container)
{
	index_ = index;
	container_ref_ = container;
}

void UBuffWidget::BeginBuffUI(FBuffData buff_data)
{
	SetVisibility(ESlateVisibility::Visible);
	buff_data_cache_ = buff_data;
	left_time_ = buff_data.duration_;
	is_available_ = false;

	if(buff_data.thumbnail != nullptr)
	{
		FSlateBrush brush;
		brush.SetResourceObject(buff_data.thumbnail);

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
	if (left_time_ > 0)
	{
		left_time_ -= InDeltaTime;
		left_time_ = FMath::Max(left_time_, 0.f);
		buff_image_->SetPercent(left_time_ / buff_data_cache_.duration_);
	}
}

float UBuffWidget::GetLeftTime() const
{
	return left_time_;
}

FBuffData UBuffWidget::GetBuffDataCache() const
{
	return buff_data_cache_;
}

FProgressBarStyle UBuffWidget::GetProgressBarStyle() const
{
	return buff_image_->GetWidgetStyle();
}

void UBuffWidget::ResetWidget()
{
	SetVisibility(ESlateVisibility::Hidden);
	left_time_ = 0;
	is_available_ = true;
	buff_data_cache_ = FBuffData();
}

void UBuffWidget::SetWidget(const FProgressBarStyle& style, const FBuffData& data_cache, float left_time,
	bool is_available)
{
	if(is_available)
	{
		ResetWidget();
	}
	else
	{
		buff_image_->SetWidgetStyle(style);
		buff_data_cache_ = data_cache;
		left_time_ = left_time;
		is_available_ = is_available;
	}
}

bool UBuffWidget::IsWidgetAvailable() const
{
	return is_available_;
}
