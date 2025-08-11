/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.13.2025
Summary : Source file for Skill Popup widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/PopUps/BasicPopupWidget.h"
#include "Components/Image.h"
#include "Components/RichTextBlock.h"

void UBasicPopupWidget::UpdatePopupData(UTexture2D* thumbnail, const FText& name, const FText& detail)
{
	SetVisibility(ESlateVisibility::Visible);
	thumbnail_->SetBrushFromTexture(thumbnail);
	name_->SetText(name);
	detail_->SetText(detail);
}

void UBasicPopupWidget::ResetWidget()
{
	SetVisibility(ESlateVisibility::Hidden);
	thumbnail_->SetBrushFromTexture(nullptr);
}
