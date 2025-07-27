/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 7.23.2025
Summary : Source file for Enemy HP UI.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/EnemyHPUI.h"
#include "UI/BuffContainer.h"

void UEnemyHPUI::InitEnemyHPUI(UBuffPopupWidget* popup_widget)
{
	buff_container_->InitBuffContainer(popup_widget);
}

void UEnemyHPUI::OnToggleDetailMode(bool on_focus_mode)
{
	if (on_focus_mode)
	{
		buff_container_->UpdateWidgetSize(50);
	}
	else
	{
		buff_container_->UpdateWidgetSize(25);
	}
}

TObjectPtr<UHPUICore> UEnemyHPUI::GetHPUICore()
{
	return hp_widget_;
}

TObjectPtr<UBuffContainer> UEnemyHPUI::GetBuffContainer()
{
	return buff_container_;
}