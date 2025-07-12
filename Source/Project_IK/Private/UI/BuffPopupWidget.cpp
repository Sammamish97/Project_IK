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
#include "Structs/BuffUIData.h"

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

void UBuffPopupWidget::SetBuffDetail(FBuffUIData target_data)
{
	//IKTODO: 한번씩 INVALID가 들어온다. 이유를 알아야 한다.
	if(target_data.buff_type_!=EBuffType::INVALID)
	{
		SetVisibility(ESlateVisibility::Visible);
		thumbnail_->SetBrushFromTexture(target_data.thumbnail);
		name_->SetText(target_data.buff_name_);
		detail_->SetText(target_data.detail_);
	}
}