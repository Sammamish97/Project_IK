/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.05.2025
Summary : Source file for HP UI widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/HP_UI_Widget.h"
#include "Components/ProgressBar.h"

void UHP_UI_Widget::InitHPWidget(float max_hp)
{
	max_hp_ = max_hp;
	temp_max_hp_ = max_hp;
}

void UHP_UI_Widget::OnHPChanged(float hp_ratio)
{
	cur_hp_ = max_hp_ * hp_ratio;
	hp_bar_->SetPercent(hp_ratio);
}

void UHP_UI_Widget::OnShieldChanged(float shield_ratio)
{
	if (cur_hp_ + shield_ratio > max_hp_)
	{
	}
}
