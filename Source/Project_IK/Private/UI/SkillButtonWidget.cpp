/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.03.2025
Summary : Source file for Skill Button Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/SkillButtonWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void USkillButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();
	cool_down_text_->SetVisibility(ESlateVisibility::Hidden);
}

void USkillButtonWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void USkillButtonWidget::OnSkillInvoked(float cool_time)
{
	cool_time_ = cool_time;
	left_cool_down_ = cool_time;
}

void USkillButtonWidget::SetThumbnailTexture(UTexture2D* thumbnail)
{
	if (thumbnail)
	{
		FSlateBrush brush;
		brush.SetResourceObject(thumbnail);

		FProgressBarStyle style;
		style.BackgroundImage = brush;
	
		style.FillImage = brush;
		style.FillImage.TintColor = FLinearColor(0.2f, 0.2f, 0.2f);
	
		progress_bar_->SetWidgetStyle(style);
	}
	else
	{
		FSlateBrush brush;
		FProgressBarStyle style;
		brush.SetResourceObject(empty_texture_);
		
		style.BackgroundImage = brush;
		style.FillImage = brush;
		
		progress_bar_->SetWidgetStyle(style);
	}
}

void USkillButtonWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	if (left_cool_down_ > 0)
	{
		left_cool_down_ -= InDeltaTime;
		left_cool_down_ = FMath::Max(left_cool_down_, 0.f);
		cool_down_text_->SetVisibility(ESlateVisibility::Visible);
		cool_down_text_->SetText(FText::AsNumber(left_cool_down_));
		progress_bar_->SetPercent(left_cool_down_/cool_time_);
	}
	else
	{
		cool_down_text_->SetVisibility(ESlateVisibility::Hidden);
	}
}
