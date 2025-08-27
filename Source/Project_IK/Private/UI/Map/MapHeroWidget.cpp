/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 8.24.2025
Summary : Source file for Map Hero Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/Map/MapHeroWidget.h"

#include "Components/Border.h"
#include "Components/Image.h"
#include "UI/Combat/BuffContainer.h"
#include "UI/Combat/SegmentedHPUI.h"

void UMapHeroWidget::InitMapHeroWidget(float max_hp, float cur_hp, const FHeroData& hero_data)
{
	hp_bar_->InitHPWidget(max_hp, cur_hp);
	color_border_->SetBrushColor(hero_data.widget_color_);
	hp_bar_->SetHPBarColor(hero_data.hp_bar_color_);
	hero_portrait_->SetBrushFromTexture(hero_data.portrait_);
}

USegmentedHPUI* UMapHeroWidget::GetHPWidget()
{
	return hp_bar_;
}