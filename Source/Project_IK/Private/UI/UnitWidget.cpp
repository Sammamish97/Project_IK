/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.09.2025
Summary : Source file for Unit widget UI.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "UI/UnitWidget.h"
#include "UI/BuffContainer.h"
#include "Components/Border.h"
#include "UI/SegmentedHPUI.h"
#include "UI/MiniRuneBoardWidget.h"


void UHeroWidget::InitHeroWidget(UBuffPopupWidget* popup_widget, URuneMechanics* rune_mechanics,
	URunePopupWidget* rune_popup_widget, EHeroType hero_type, FColor hero_base_color_1, FColor hero_base_color_2, float max_hp,
	float cur_hp)
{
	buff_container_->InitBuffContainer(popup_widget);
	hp_bar_->InitHPWidget(max_hp, cur_hp);
	mini_rune_board_->InitMiniRuneBoard(rune_mechanics, rune_popup_widget, hero_type);
	color_border_->SetBrushColor(hero_base_color_1);
	hp_bar_->SetHPBarColor(hero_base_color_2);
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