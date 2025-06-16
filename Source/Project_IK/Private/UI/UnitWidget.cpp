/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.09.2025
Summary : Source file for Unit widget UI.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "UI/UnitWidget.h"

#include "Blueprint/WidgetTree.h"
#include "Components/HorizontalBox.h"
#include "Components/RuneMechanics.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/DataTableManager.h"
#include "Structs/BuffData.h"
#include "UI/BuffDisplayer.h"
#include "UI/SegmentedHPUI.h"
#include "UI/MiniRuneBoardWidget.h"
#include "UI/SkillButtonWidget.h"
#include "WorldSettings/IKGameInstance.h"

void UHeroWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UHeroWidget::InitHeroWidget(URuneMechanics* rune_mechanics,float max_hp, float cur_hp)
{
	hp_bar_->InitHPWidget(max_hp, cur_hp);
	mini_rune_board_->InitMiniRuneBoard(rune_mechanics);
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