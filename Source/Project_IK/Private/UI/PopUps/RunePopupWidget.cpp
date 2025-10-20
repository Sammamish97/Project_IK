/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.17.2025
Summary : Source file for Rune Popup Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "UI/PopUps/RunePopupWidget.h"

#include "Components/Image.h"
#include "Components/RuneMechanics.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "Components/RichTextBlock.h"
#include "DataAssets/RuneDataAsset.h"
#include "Managers/DataTableManager.h"
#include "Managers/TextManager.h"
#include "UI/PopUps/RunePopupDetailWidget.h"
#include "WorldSettings/IKGameInstance.h"

void URunePopupWidget::InitSetBonusDetails(const TMap<EHeroType, TArray<RuneSetBonus>>& bonus_details)
{
	bonus_details_ = bonus_details;
	
	auto instance = Cast<UIKGameInstance>(GetGameInstance());
	text_manager_cache_ = instance->GetTextManager();
	data_table_cache_ = instance->GetDataTableManager();

	title_text_->SetText(text_manager_cache_->GetPopUpText("RUNESETTITLE"));
}

void URunePopupWidget::UpdateRuneData(EHeroType type)
{
	SetVisibility(ESlateVisibility::Visible);
	auto cur_hero_data = bonus_details_[type];

	for (const auto& elem : cur_hero_data)
	{
		ERuneSetType rune_type = elem.Key;
		ERuneSetBonusType bonus_type_ = ERuneSetBonusType::INVALID;
		switch (elem.Value.Num())
		{
		case 2:
			bonus_type_ = ERuneSetBonusType::Edge;
			break;
			
		case 3:
			bonus_type_ = ERuneSetBonusType::Triangle;
			break;
			
		case 6:
			bonus_type_ = ERuneSetBonusType::Hexagon;
			break;
		}
		
		auto new_widget = CreateWidget<URunePopupDetailWidget>(this, rune_popup_detail_widget_class_);
		new_widget->thumbnail_->SetBrushFromTexture( data_table_cache_->GetRuneSetThumbnail(elem.Key));
		new_widget->set_bonus_type_->SetText(text_manager_cache_->GetRuneNameText(rune_type));
		new_widget->set_bonus_detail_->SetText(text_manager_cache_->GetRuneSetBonusText(rune_type, bonus_type_));
		new_widget->AddToViewport();
		vertical_box_->AddChildToVerticalBox(new_widget);
		details_.Push(new_widget);
	}
}

void URunePopupWidget::ResetWidget()
{
	SetVisibility(ESlateVisibility::Hidden);
	vertical_box_->ClearChildren();
	details_.Empty();
}