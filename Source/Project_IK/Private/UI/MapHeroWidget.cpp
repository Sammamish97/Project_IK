/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.24.2025
Summary : Source file for Map Hero Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/MapHeroWidget.h"

#include "Components/Border.h"
#include "UI/BuffContainer.h"
#include "UI/SegmentedHPUI.h"

void UMapHeroWidget::InitHeroWidget(float max_hp, float cur_hp)
{
	hp_bar_->InitHPWidget(max_hp, cur_hp);
}

USegmentedHPUI* UMapHeroWidget::GetHPWidget()
{
	return hp_bar_;
}