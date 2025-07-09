/******************************************************************************
Copyright(C) 2024
Author: sinil.kang(rtd99062@gmail.com)
Creation Date : 12.02.2024
Summary : Source file for UI to display how much damage dealt.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/


#include "UI/DamageWidget.h"

#include "Components/TextBlock.h"

void UDamageWidget::SetDamageAmount(float DamageAmount)
{
	FNumberFormattingOptions format_options;
	format_options.MinimumIntegralDigits = 1;
	format_options.MinimumFractionalDigits = 1;
	format_options.MaximumFractionalDigits = 1;
	damage_text_->SetText(FText::AsNumber(DamageAmount, &format_options));
	opacity_ = 1.f;
}

void UDamageWidget::SetMissed()
{
	damage_text_->SetText(NSLOCTEXT("UI", "DamageUIMissed", "Missed"));
	opacity_ = 1.f;
}

void UDamageWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	if (opacity_ <= 0.f)
	{
		return;
	}

	static constexpr float speed = 1.f / 0.75f;
	opacity_ -= InDeltaTime * speed;
	SetRenderOpacity(opacity_);
}
