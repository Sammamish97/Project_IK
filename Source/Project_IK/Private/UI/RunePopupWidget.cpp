/******************************************************************************
Copyright(C) 2025
Author: chunmook.kim(chunmook.kim97@gmail.com)
Creation Date : 6.17.2025
Summary : Source file for Rune Popup Widget.

Licensed under the MIT License.
See LICENSE file in the project root for full license information.
******************************************************************************/
#include "UI/RunePopupWidget.h"
#include "Components/RuneMechanics.h"
#include "Components/TextBlock.h"

void URunePopupWidget::InitSetBonusDetails(const TMap<EHeroType, TArray<FString>> bonus_details)
{
	bonus_details_ = bonus_details;
}

void URunePopupWidget::UpdateRuneData(EHeroType type)
{
	SetVisibility(ESlateVisibility::Visible);
	int32 detail_idx_ = 0;
	TArray details = {detail_0_, detail_1_, detail_2_, detail_3_};
	for(const auto& elem : bonus_details_[type])
	{
		details[detail_idx_++]->SetText(FText::FromString(elem));
	}
}

void URunePopupWidget::ResetWidget()
{
	SetVisibility(ESlateVisibility::Hidden);
	TArray details = {detail_0_, detail_1_, detail_2_, detail_3_};
	for(const auto& elem : details)
	{
		elem->SetText(FText::FromString(""));
	}
}