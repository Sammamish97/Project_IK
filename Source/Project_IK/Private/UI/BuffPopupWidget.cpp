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
	name_->SetText(NSLOCTEXT("UI", "BuffPopupName", "name"));
	detail_->SetText(NSLOCTEXT("UI", "BuffPopupDetail", "detail"));
}

void UBuffPopupWidget::SetBuffDetail(UDisplayDataAsset* target_data)
{
	if (target_data)
	{
		SetVisibility(ESlateVisibility::Visible);
		thumbnail_->SetBrushFromTexture(target_data->thumbnail);
		name_->SetText(target_data->name_);
		//IKTODO: Evaluate에 적절한 값을 넣어야 한다.
		//detail_->SetText(target_data.item_data_.detail_.Evaluate());
	}
}
