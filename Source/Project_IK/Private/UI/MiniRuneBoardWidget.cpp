/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.04.2025
Summary : Source file for Mini Rune Board widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/MiniRuneBoardWidget.h"
#include "Characters/HeroBase.h"
#include "Components/RuneMechanics.h"

void UMiniRuneBoardWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMiniRuneBoardWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UMiniRuneBoardWidget::InitMiniRuneBoard(AHeroBase* owner)
{
	owner_hero_ = owner;
	auto equipped_rune_data = owner_hero_->GetRuneMechanics();
	auto rune_data_array = equipped_rune_data->GetEquippedRunes();
}
