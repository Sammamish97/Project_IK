/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.12.2025
Summary : Source file for HP UI Core widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/HPUICore.h"
#include "Components/ProgressBar.h"

void UHPUICore::InitHPWidget(float max_hp, float cur_hp)
{
	max_hp_ = max_hp;
	cur_max_hp_ = max_hp_;
	UpdateWidget(cur_hp, 0);
}

void UHPUICore::UpdateWidget(float cur_hp, float cur_shield)
{
	cur_max_hp_ = FMath::Max(cur_hp + cur_shield, max_hp_);
	float hp_ratio = cur_hp / cur_max_hp_;
	float shield_ratio = hp_ratio + cur_shield / cur_max_hp_;

	hp_bar_->SetPercent(hp_ratio);
	shield_bar_->SetPercent(shield_ratio);
}

void UHPUICore::SetHPBarColor(FLinearColor color)
{
	FProgressBarStyle style;
	style.FillImage.TintColor = color;
	style.BackgroundImage.TintColor = FLinearColor::Transparent;
	hp_bar_->SetWidgetStyle(style);
}