/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.16.2025
Summary : Source file for Buff Popup Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/

#include "UI/BuffPopupWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Structs/BuffData.h"

void UBuffPopupWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetVisibility(ESlateVisibility::Hidden);
}

void UBuffPopupWidget::ResetWidget()
{
	SetVisibility(ESlateVisibility::Hidden);
	thumbnail_->SetBrushFromTexture(nullptr);
	name_->SetText(FText::FromString(""));
	detail_->SetText(FText::FromString(""));
}

void UBuffPopupWidget::SetBuffDetail(FBuffData target_data)
{
	SetVisibility(ESlateVisibility::Visible);
	thumbnail_->SetBrushFromTexture(target_data.thumbnail);
	name_->SetText(target_data.buff_name_);
	detail_->SetText(FText::FromString(target_data.detail_));
}