/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.12.2025
Summary : Source file for Support Skill Button Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/SupportSkillButtonWidget.h"
#include "Components/TextBlock.h"

void USupportSkillButtonWidget::SetSupportSkillCost(int32 cost)
{
	cost_text_->SetText(FText::AsNumber(cost));
}
