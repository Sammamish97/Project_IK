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
#include "DataAssets/RuneDataAsset.h"
#include "Managers/DataTableManager.h"
#include "UI/PopUps/RunePopupDetailWidget.h"
#include "WorldSettings/IKGameInstance.h"

void URunePopupWidget::InitSetBonusDetails(const TMap<EHeroType, TArray<RuneSetBonus>>& bonus_details)
{
	bonus_details_ = bonus_details;
}

void URunePopupWidget::UpdateRuneData(EHeroType type)
{
	SetVisibility(ESlateVisibility::Visible);

	UDataTableManager* data_table_cache_ = Cast<UIKGameInstance>(GetGameInstance())->GetDataTableManager();

	auto cur_hero_data = bonus_details_[type];

	for (const auto& elem : cur_hero_data)
	{
		ERuneSetBonusType bonus_type_ = ERuneSetBonusType::INVALID;
		FText bonus_type_text;
		switch (elem.Value.Num())
		{
		case 2:
			bonus_type_ = ERuneSetBonusType::Edge;
			bonus_type_text = NSLOCTEXT("UI", "RunePopupBonusTypeEdge", "Edge: ");
			break;
			
		case 3:
			bonus_type_ = ERuneSetBonusType::Triangle;
			bonus_type_text = NSLOCTEXT("UI", "RunePopupBonusTypeTriangle", "Triangle: ");
			break;
			
		case 6:
			bonus_type_ = ERuneSetBonusType::Hexagon;
			bonus_type_text = NSLOCTEXT("UI", "RunePopupBonusTypeHexagon", "Hexagon: ");
			break;
		}

		auto cur_set_data = data_table_cache_->GetRuneSetData(elem.Key);
		
		auto new_widget = CreateWidget<URunePopupDetailWidget>(this, rune_popup_detail_widget_class_);
		new_widget->thumbnail_->SetBrushFromTexture(cur_set_data.thumbnail_);
		new_widget->set_bonus_type_->SetText(bonus_type_text);
		//IKTODO: String table 사용하기.
		//new_widget->set_bonus_detail_->SetText(cur_set_data.bonus_details_[bonus_type_]);
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