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
#include "DataAssets/DisplayDataAsset.h"

void UBuffPopupWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UBuffPopupWidget::ResetWidget()
{
	SetVisibility(ESlateVisibility::Hidden);
	thumbnail_->SetBrushFromTexture(nullptr);
}

void UBuffPopupWidget::SetBuffDetail(UDisplayDataAsset* target_data)
{
	if (target_data)
	{
		SetVisibility(ESlateVisibility::Visible);
		thumbnail_->SetBrushFromTexture(target_data->thumbnail);
		FText name = FText::FromStringTable("/Game/StringTables/Names", target_data->text_key_);
		FText detail = FText::FromStringTable("/Game/StringTables/Details", target_data->text_key_);

		name_->SetText(name);
		detail_->SetText(detail);
	}
}
