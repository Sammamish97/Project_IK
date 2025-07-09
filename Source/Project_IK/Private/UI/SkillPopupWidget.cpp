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
#include "Managers/EnumCluster.h"
#include "Structs/ItemData.h"

void USkillPopupWidget::InitHeroSkillData(const TMap<EHeroType, FItemData>& input_data)
{
	hero_skill_data_ = input_data;
}

void USkillPopupWidget::InitSupportSkillData(const TMap<int32, FItemData>& input_data)
{
	support_skill_data_ = input_data;
}

void USkillPopupWidget::UpdateSkillPopupData(EHeroType type)
{
	SetVisibility(ESlateVisibility::Visible);
	thumbnail_->SetBrushFromTexture(hero_skill_data_[type].thumbnail);
	skill_name_->SetText(hero_skill_data_[type].name_);
	skill_detail_->SetText(hero_skill_data_[type].detail_.Evaluate({}));
}

void USkillPopupWidget::UpdateSkillPopupData(int32 support_skill_idx)
{
	SetVisibility(ESlateVisibility::Visible);
	thumbnail_->SetBrushFromTexture(support_skill_data_[support_skill_idx].thumbnail);
	skill_name_->SetText(support_skill_data_[support_skill_idx].name_);
	skill_detail_->SetText(support_skill_data_[support_skill_idx].detail_.Evaluate({}));
}
