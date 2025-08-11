/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.13.2025
Summary : Source file for Skill Popup widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/SkillPopupWidget.h"
#include "Components/Image.h"
#include "Components/RichTextBlock.h"

void USkillPopupWidget::UpdatePopupData(UTexture2D* thumbnail, const FText& name, const FText& detail)
{
	SetVisibility(ESlateVisibility::Visible);
	thumbnail_->SetBrushFromTexture(thumbnail);
	skill_name_->SetText(name);
	skill_detail_->SetText(detail);
}
