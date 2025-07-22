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
#include "Structs/ItemData.h"

void USkillPopupWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetVisibility(ESlateVisibility::Hidden);
}

void USkillPopupWidget::UpdatePopupData(const FItemData& item_data)
{
	thumbnail_->SetBrushFromTexture(item_data.display_data_->thumbnail);
	skill_name_->SetText(item_data.display_data_->name_);
	//IKTODO: 이후 적절한 값을 Evaluate에 넣어야 한다.
	//skill_detail_->SetText(item_data.detail_.Evaluate());
}
