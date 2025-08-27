/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.09.2025
Summary : Source file for Unit widget UI.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "UI/Combat/HeroWidget.h"
#include "UI/Combat/BuffContainer.h"
#include "Components/Border.h"
#include "Structs/HeroData.h"
#include "UI/Combat/SegmentedHPUI.h"
#include "UI/Combat/MiniRuneBoardWidget.h"

void UHeroWidget::InitHeroWidget(UBasicPopupWidget* popup_widget, class URuneMechanics* rune_mechanics,
                                 class URunePopupWidget* rune_popup_widget, EHeroType hero_type, float max_hp, float cur_hp,
                                 const FHeroData& hero_data)
{
	buff_container_->InitBuffContainer(popup_widget);
	hp_bar_->InitHPWidget(max_hp, cur_hp);
	mini_rune_board_->InitMiniRuneBoard(rune_mechanics, rune_popup_widget, hero_type);
	color_border_->SetBrushColor(hero_data.widget_color_);
	hp_bar_->SetHPBarColor(hero_data.hp_bar_color_);
}

USegmentedHPUI* UHeroWidget::GetHPWidget()
{
	return hp_bar_;
}

USkillButtonWidget* UHeroWidget::GetSkillButtonWidget()
{
	return skill_button_widget_;
}

UBuffContainer* UHeroWidget::GetBuffContainer()
{
	return buff_container_;
}