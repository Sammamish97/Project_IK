/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 01.08.2025
Summary : Source file of checkbox button.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/CheckboxButtonWidget.h"

#include "Components/Button.h"
#include "Components/Image.h"

bool UCheckboxButtonWidget::Initialize()
{
	Super::Initialize();

	is_checked_ = false;
	return true;
}

void UCheckboxButtonWidget::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	UpdateImageColor();
}

void UCheckboxButtonWidget::SetButtonTexture(UTexture2D* texture)
{
	FButtonStyle button_style;
	FSlateBrush new_brush;
	new_brush.SetResourceObject(texture);
	new_brush.DrawAs = ESlateBrushDrawType::Type::Image;
	new_brush.TintColor = FSlateColor(normal_color);
	new_brush.SetImageSize(FDeprecateSlateVector2D(128.f, 128.f));
	button_style.SetNormal(new_brush);
	new_brush.TintColor = FSlateColor(hovered_color);
	button_style.SetHovered(new_brush);
	new_brush.TintColor = FSlateColor(pressed_color);
	button_style.SetPressed(new_brush);
	button_->SetStyle(button_style);
}

void UCheckboxButtonWidget::SetIsChecked(bool flag)
{
	if (flag != is_checked_)
	{
		ToggleChecked();
	}
}

void UCheckboxButtonWidget::ToggleChecked()
{
	is_checked_ = !is_checked_;
	
	selection_indicator_image_->SetVisibility(is_checked_ ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Hidden);
}

void UCheckboxButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	selection_indicator_image_->SetVisibility(is_checked_ ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Hidden);

	if (button_)
	{
		button_->OnClicked.AddDynamic(this, &UCheckboxButtonWidget::OnButtonClicked);
	}

}

void UCheckboxButtonWidget::NativeDestruct()
{
	if (button_)
	{
		button_->OnClicked.Clear();
	}
	OnCheckboxButtonClickedDelegate.Clear();
}

void UCheckboxButtonWidget::UpdateImageColor()
{
	// Retrieve the button's current state from its style
	const FButtonStyle& ButtonStyle = button_->GetStyle();

	// Determine the appropriate color based on the button's state
	FSlateColor CurrentColor;
	if (button_->IsPressed())
	{
		CurrentColor = ButtonStyle.Pressed.TintColor;
	}
	else if (button_->IsHovered())
	{
		CurrentColor = ButtonStyle.Hovered.TintColor;
	}
	else
	{
		CurrentColor = ButtonStyle.Normal.TintColor;
	}

	// Apply the color to the image
	selection_indicator_image_->SetColorAndOpacity(CurrentColor.GetSpecifiedColor());
}

void UCheckboxButtonWidget::OnButtonClicked()
{
	ToggleChecked();

	if (OnCheckboxButtonClickedDelegate.IsBound())
	{
		OnCheckboxButtonClickedDelegate.Broadcast();
	}
}