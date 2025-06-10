/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.06.2025
Summary : Source file for Hero widget UI.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "UI/HeroWidget.h"
#include "UI/MiniRuneBoardWidget.h"

void UHeroWidget::InitHeroWidget(URuneMechanics* rune_mechanics, float max_hp, float cur_hp)
{
	InitUnitWidget(max_hp, cur_hp);
	mini_rune_board_->InitMiniRuneBoard(rune_mechanics);
}